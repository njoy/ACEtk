#ifndef NJOY_ACETK_CONTINUOUS_ENERGYDEPENDENTWATTSPECTRUM
#define NJOY_ACETK_CONTINUOUS_ENERGYDEPENDENTWATTSPECTRUM

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/continuous/ParameterData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief An energy dependent Watt spectrum
 *
 *  The EnergyDependentWattSpectrum class contains the tabulated values for the
 *  energy dependent a and b parameters as well as the restriction energy U used
 *  to describe the Watt spectrum. It is used in the DLW block as ACE LAW 11.
 */
class EnergyDependentWattSpectrum : protected base::Base {

  /* fields */
  ParameterData a_;
  ParameterData b_;

  /* auxiliary functions */
  #include "ACEtk/continuous/EnergyDependentWattSpectrum/src/verifySize.hpp"
  #include "ACEtk/continuous/EnergyDependentWattSpectrum/src/generateBlocks.hpp"
  #include "ACEtk/continuous/EnergyDependentWattSpectrum/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/EnergyDependentWattSpectrum/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::Watt;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::Watt;
  }

  /**
   *  @brief Return the data for the a parameter
   */
  const ParameterData& a() const { return this->a_; }

  /**
   *  @brief Return the data for the b parameter
   */
  const ParameterData& b() const { return this->b_; }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return this->a().energies().front();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return this->a().energies().back();
  }

  /**
   *  @brief Return the restriction energy
   */
  double U() const { return *this->b_.end(); }

  /**
   *  @brief Return the restriction energy
   */
  double restrictionEnergy() const { return this->U(); }

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
