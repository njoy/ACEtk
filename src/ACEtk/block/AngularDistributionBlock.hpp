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
 *  The AngularDistributionBlock class contains angular distribution data,
 *  one for each the first NXS(5) reaction numbers on the MTR block and
 *  elastic as well (referenced using the reaction index 0). Elastic is always
 *  the first reaction (hence the index 0 for this reaction) while the order
 *  of the other distribution data sets is the same as the order of the reaction
 *  numbers in the MTR block.
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
  std::size_t offset_;

  /* auxiliary functions */
  #include "ACEtk/block/AngularDistributionBlock/src/insertElastic.hpp"
  #include "ACEtk/block/AngularDistributionBlock/src/generateXSS.hpp"
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
    this->verifyReactionIndex( index, this->offset_ == 1 ? 0 : 1, this->NR() );
    #endif
    return XSS( index + this->offset_ ); // elastic is index 0
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
        const std::size_t xand = std::distance( this->begin(), this->and_ ) + 1;
        const std::size_t land = this->LAND( index );
        const auto locator = xand + land - 1;
        const auto left = this->iterator( locator );
        auto right = this->end();
        for ( auto next = index + 1; next <= this->NR(); ++next ) {

          auto nextlocator = xand + this->LAND( next ) - 1;
          if ( nextlocator > locator ) {

            right = this->iterator( nextlocator );
            break;
          }
        }
        return AngularDistributionData( land, left, right );
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
