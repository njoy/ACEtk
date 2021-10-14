#ifndef NJOY_ACETK_BLOCK_ANGULARDISTRIBUTIONDATA
#define NJOY_ACETK_BLOCK_ANGULARDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "utility/overload.hpp"
#include "ACEtk/block/Base.hpp"
#include "ACEtk/block/EquiprobableAngularBins.hpp"
#include "ACEtk/block/TabulatedAngularDistribution.hpp"
#include "ACEtk/block/IsotropicAngularDistribution.hpp"
#include "ACEtk/AngularDistributionType.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Angular distribution data from the AND block for a single reaction
 */
class AngularDistributionData : protected Base {

public:

  /* type alias */
  using Distribution = std::variant< IsotropicAngularDistribution,
                                     EquiprobableAngularBins,
                                     TabulatedAngularDistribution >;

private:

  /* fields */
  std::size_t locb_;

  /* auxiliary functions */
  #include "ACEtk/block/AngularDistributionData/src/generateXSS.hpp"
  #include "ACEtk/block/AngularDistributionData/src/verifyIncidentEnergyIndex.hpp"
  #include "ACEtk/block/AngularDistributionData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/AngularDistributionData/src/ctor.hpp"

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the incident energy values
   */
  auto incidentEnergies() const {

    return this->XSS( 2, this->numberIncidentEnergies() );
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
    return this->XSS( 1 + index );
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
    return XSS( 1 + this->numberIncidentEnergies() + index );
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
  int angularDistributionLocator( std::size_t index ) const {

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
  std::size_t relativeAngularDistributionLocator( std::size_t index ) const {

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
  AngularDistributionType angularDistributionType( std::size_t index ) const {

    const auto locator = this->angularDistributionLocator( index );
    return locator == 0
           ? AngularDistributionType::Isotropic
           : locator < 0 ? AngularDistributionType::Tabulated
                         : AngularDistributionType::Equiprobable;
  }

  /**
   *  @brief Return the angular distribution data for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  Distribution angularDistributionData( std::size_t index ) const {

    const auto type = this->angularDistributionType( index );
    const auto locator = this->relativeAngularDistributionLocator( index );
    const double incident = this->incidentEnergy( index );
    if ( type == AngularDistributionType::Isotropic ) {

        return IsotropicAngularDistribution( incident );
    }
    else {

      const auto left = std::next( this->begin(), locator - 1 );
      const auto right = index == this->numberIncidentEnergies()
          ? this->end()
          : std::next( this->begin(),
                       ( this->relativeAngularDistributionLocator( index + 1 ) - 1 ) );
      if ( type == AngularDistributionType::Tabulated ) {

        return TabulatedAngularDistribution( incident, left, right );
      }
      else {

        return EquiprobableAngularBins( incident, left, right );
      }
    }
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
