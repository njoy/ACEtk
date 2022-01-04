#ifndef NJOY_ACETK_BLOCK_ANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_ANGULARDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/BaseAngularDistributionBlock.hpp"

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
class AngularDistributionBlock : protected details::BaseAngularDistributionBlock {

public:

  /* type alias */
  using DistributionData = std::variant< FullyIsotropicDistribution,
                                         DistributionGivenElsewhere,
                                         AngularDistributionData >;

private:

  /* fields */
  unsigned int nr_;   // number of reactions that produce the projectile (excluding elastic)
  Iterator iterator_; // the begin iterator of the AND block
  std::vector< DistributionData > data_;
  bool zero_index_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/AngularDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int NR() const {

    return BaseAngularDistributionBlock::NR();
  }

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic)
   */
  unsigned int numberProjectileProductionReactions() const {

    return BaseAngularDistributionBlock::numberReactions();
  }

  /**
   *  @brief Return the total number of reactions that produce the projectile
   *         (including elastic)
   */
  unsigned int totalNumberProjectileProductionReactions() const {

    return this->NR() + 1;
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
  int LAND( std::size_t index ) const {

    return BaseAngularDistributionBlock::LAND( index );
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

    return BaseAngularDistributionBlock::angularDistributionLocator( index );
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

    return BaseAngularDistributionBlock::isFullyIsotropic( index );
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

    return BaseAngularDistributionBlock::isGiven( index );
  }

//  /**
//   *  @brief Return all angular distribution data
//   */
//  const std::vector< DistributionData >& angularDistributionData() const {
//
//    return BaseAngularDistributionBlock::angularDistributionData();
//  }

  /**
   *  @brief Return the angular distribution data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DistributionData& angularDistributionData( std::size_t index ) const {

    return BaseAngularDistributionBlock::angularDistributionData( index );
  }

  using BaseAngularDistributionBlock::empty;
  using BaseAngularDistributionBlock::name;
  using BaseAngularDistributionBlock::length;
  using BaseAngularDistributionBlock::XSS;
  using BaseAngularDistributionBlock::begin;
  using BaseAngularDistributionBlock::end;
};

using AND = AngularDistributionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
