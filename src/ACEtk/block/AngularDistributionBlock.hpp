#ifndef NJOY_ACETK_BLOCK_ANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_ANGULARDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/AngularDistributionData.hpp"
#include "ACEtk/block/FullyIsotropicDistribution.hpp"
#include "ACEtk/block/DistributionGivenElsewhere.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy LAND and AND block with the angular
 *         distribution data
 *
 *  The AngularDistributionBlock class contains NXS(4) sets of angular
 *  distribution data (either ),
 *  one for each reaction number on the MTR block. The order of these cross
 *  section data sets is the same as the order of the reaction numbers in the
 *  MTR block.
 */
class AngularDistributionBlock : protected details::Base {

public:

  /* type alias */
  using DistributionData = std::variant< FullyIsotropicDistribution,
                                         DistributionGivenElsewhere,
                                         AngularDistributionData >;

private:

  /* fields */
  unsigned int nr_; // number of reactions that produce the projectile (excluding elastic)
  Iterator and_;    // the begin iterator of the AND block

  /* auxiliary functions */
  #include "ACEtk/block/AngularDistributionBlock/src/generateXSS.hpp"
  #include "ACEtk/block/AngularDistributionBlock/src/verifyReactionIndex.hpp"
  #include "ACEtk/block/AngularDistributionBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/AngularDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int NR() const { return this->nr_; }

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int numberProjectileProductionReactions() const { return this->NR(); }

  /**
   *  @brief Return the relative angular distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based, zero for elastic)
   */
  int LAND( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyReactionIndex( index );
    #endif
    return XSS( index + 1 ); // elastic is index 0
  }

  /**
   *  @brief Return the relative angular distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based, zero for elastic)
   */
  int angularDistributionLocator( std::size_t index ) const {

    return this->LAND( index );
  }

  /**
   *  @brief Return whether or not the distribution data is fully isotropic for
   *         a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based, zero for elastic)
   */
  bool isFullyIsotropic( std::size_t index ) const {

    return this->LAND( index ) == 0;
  }

  /**
   *  @brief Return whether or not the distribution data for a reaction index
   *         is given in the AND block
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based, zero for elastic)
   */
  bool isGiven( std::size_t index ) const {

    return this->LAND( index ) >= 0;
  }

  /**
   *  @brief Return the angular distribution data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based, zero for elastic)
   */
  DistributionData angularDistributionData( std::size_t index ) const {

    if ( this->isGiven( index ) ) {

      if ( this->isFullyIsotropic( index ) ) {

        return FullyIsotropicDistribution();
      }
      else {

        // xand : one-based index to the start of the AND block
        // xand + locator - 1 : one-based index to the start of distribution data
        std::size_t xand = std::distance( this->begin(), this->and_ ) + 1;
        const auto locator = xand + this->LAND( index ) - 1;
        const auto left = std::next( this->begin(), locator - 1 );
        auto right = this->end();
        for ( auto next = index + 1;
              next <= this->numberProjectileProductionReactions(); ++next ) {

          auto nextlocator = xand + this->LAND( index ) - 1;
          if ( nextlocator > locator ) {

            right = std::next( this->begin(), nextlocator - 1 );
            break;
         }
        }
        return AngularDistributionData( locator - ( xand - 1 ), left, right );
      }
    }
    else {

      return DistributionGivenElsewhere();
    }
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using AND = AngularDistributionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
