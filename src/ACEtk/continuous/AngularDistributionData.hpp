#ifndef NJOY_ACETK_CONTINUOUS_ANGULARDISTRIBUTIONDATA
#define NJOY_ACETK_CONTINUOUS_ANGULARDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "utility/overload.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/continuous/EquiprobableAngularBins.hpp"
#include "ACEtk/continuous/TabulatedAngularDistribution.hpp"
#include "ACEtk/continuous/IsotropicAngularDistribution.hpp"
#include "ACEtk/AngularDistributionType.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Angular distribution data
 *
 *  The AngularDistributionData class contains the angular distribution data
 *  energy distributions for a set of incident energy values. It is used in
 *  the AND block.
 */
class AngularDistributionData : protected base::Base {

public:

  /* type alias */
  using Distribution = std::variant< IsotropicAngularDistribution,
                                     EquiprobableAngularBins,
                                     TabulatedAngularDistribution >;

private:

  /* fields */
  std::size_t locb_ = 1;
  base::ColumnData values_;
  std::vector< Distribution > distributions_;

  /* auxiliary functions */
  #include "ACEtk/continuous/AngularDistributionData/src/generateXSS.hpp"
  #include "ACEtk/continuous/AngularDistributionData/src/generateBlocks.hpp"
  #include "ACEtk/continuous/AngularDistributionData/src/verifyIncidentEnergyIndex.hpp"
  #include "ACEtk/continuous/AngularDistributionData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/AngularDistributionData/src/ctor.hpp"

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return this->values_.N(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the incident energy values
   */
  auto incidentEnergies() const {

    return this->values_.column( 1 );
  }

  /**
   *  @brief Return the incident energy for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double incidentEnergy( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->values_.value( 1, index );
  }

  /**
   *  @brief Return the angular distribution locator for an incident
   *         energy index
   *
   *  This locator is the value as stored in the XSS array. It is relative to
   *  the beginning of the AND block. The distribution type is determined from
   *  the sign of the locator:
   *    - when the value if negative, it is a tabulated distribution
   *    - when the value if positive, it is an equiprobable distribution
   *    - when the value if zero, it is an isotropic distribution
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LOCC( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->values_.value( 2, index );
  }

  /**
   *  @brief Return the angular distribution locator for an incident
   *         energy index
   *
   *  This locator is the value as stored in the XSS array. It is relative to
   *  the beginning of the AND block. The distribution type is determined from
   *  the sign of the locator:
   *    - when the value if negative, it is a tabulated distribution
   *    - when the value if positive, it is an equiprobable distribution
   *    - when the value if zero, it is an isotropic distribution
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int distributionLocator( std::size_t index ) const {

    return this->LOCC( index );
  }

  /**
   *  @brief Return the relative angular distribution locator for an incident
   *         energy index
   *
   *  This is the locator relative to the beginning of the current angular
   *  distribution block in the AND block. It is always positive.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t relativeDistributionLocator( std::size_t index ) const {

    const int locator = this->LOCC( index );
    return locator == 0 ? locator : std::abs( locator ) - this->locb_ + 1;
  }

  /**
   *  @brief Return the angular distribution type for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  AngularDistributionType distributionType( std::size_t index ) const {

    const auto locator = this->distributionLocator( index );
    return locator == 0
           ? AngularDistributionType::Isotropic
           : locator < 0 ? AngularDistributionType::Tabulated
                         : AngularDistributionType::Equiprobable;
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< Distribution >& distributions() const {

    return this->distributions_;
  }

  /**
   *  @brief Return the angular distribution data for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const Distribution& distribution( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->distributions_[ index - 1 ];
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
