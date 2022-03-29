#ifndef NJOY_ACETK_BLOCK_TABULATEDENERGYANGLEDISTRIBUTION
#define NJOY_ACETK_BLOCK_TABULATEDENERGYANGLEDISTRIBUTION

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/BaseDistributionData.hpp"
#include "ACEtk/block/TabulatedAngularDistributionWithProbability.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Tabulated outgoing energy and angle distribution data for a single
 *         incident energy
 *
 *  The TabulatedEnergyAngleDistribution class contains the
 *  tabulated angular distributions for a set of outgoing energy values and
 *  associated incident energy value. It is used in the
 *  OutgoingEnergyAngleDistributionData (ACE LAW 61) in the DLW block.
 */
class TabulatedEnergyAngleDistribution :
  protected details::BaseDistributionData< TabulatedEnergyAngleDistribution,
                                           TabulatedAngularDistributionWithProbability > {

  friend class details::BaseDistributionData< TabulatedEnergyAngleDistribution,
                                              TabulatedAngularDistributionWithProbability >;

  /* fields */
  double incident_;

  /* auxiliary functions */
  #include "ACEtk/block/TabulatedEnergyAngleDistribution/src/generateXSS.hpp"
  #include "ACEtk/block/TabulatedEnergyAngleDistribution/src/generateBlocks.hpp"

public:

  /* constructor */
  #include "ACEtk/block/TabulatedEnergyAngleDistribution/src/ctor.hpp"

  // generic function used internally
  double value() const { return this->incident_; }

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const { return this->value(); }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return BaseDistributionData::interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return BaseDistributionData::NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return BaseDistributionData::numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return BaseDistributionData::NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return BaseDistributionData::boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return BaseDistributionData::INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return BaseDistributionData::interpolants(); }

  /**
   *  @brief Return the number of outgoing energy values
   */
  std::size_t NE() const { return BaseDistributionData::N(); }

  /**
   *  @brief Return the number of outgoing energy values
   */
  std::size_t numberOutgoingEnergies() const {

    return BaseDistributionData::numberValues();
  }

  /**
   *  @brief Return the outgoing energy values
   */
  auto outgoingEnergies() const {

    return BaseDistributionData::values( 1 );
  }

  /**
   *  @brief Return the associated probability values
   */
  auto pdf() const {

    return BaseDistributionData::values( 2 );
  }

  /**
   *  @brief Return the associated cumulative probability values
   */
  auto cdf() const {

    return BaseDistributionData::values( 3 );
  }

  /**
   *  @brief Return the outgoing energy for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double outgoingEnergy( std::size_t index ) const {

    return BaseDistributionData::value( 1, index );
  }

  /**
   *  @brief Return the probability for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double probability( std::size_t index ) const {

    return BaseDistributionData::value( 2, index );
  }

  /**
   *  @brief Return the cumulative probability for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double cumulativeProbability( std::size_t index ) const {

    return BaseDistributionData::value( 3, index );
  }

  /**
   *  @brief Return the distribution locator for an outgoing energy index
   *
   *  This locator is the value as stored in the XSS array. It is relative to
   *  the beginning of the DLW block.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LOCC( std::size_t index ) const {

    return BaseDistributionData::LOCC( index );
  }

  /**
   *  @brief Return the distribution locator for an outgoing energy index
   *
   *  This locator is the value as stored in the XSS array. It is relative to
   *  the beginning of the DLW block.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int distributionLocator( std::size_t index ) const {

    return BaseDistributionData::distributionLocator( index );
  }

  /**
   *  @brief Return the relative distribution locator for an outgoing energy
   *         index
   *
   *  This is the locator relative to the beginning of the current
   *  distribution block in the DLW block.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t relativeDistributionLocator( std::size_t index ) const {

    return BaseDistributionData::relativeDistributionLocator( index );
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< TabulatedAngularDistributionWithProbability >&
  distributions() const {

    return BaseDistributionData::distributions();
  }

  /**
   *  @brief Return the distribution for an outgoing energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const TabulatedAngularDistributionWithProbability&
  distribution( std::size_t index ) const {

    return BaseDistributionData::distribution( index );
  }

  using BaseDistributionData::empty;
  using BaseDistributionData::name;
  using BaseDistributionData::length;
  using BaseDistributionData::XSS;
  using BaseDistributionData::begin;
  using BaseDistributionData::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
