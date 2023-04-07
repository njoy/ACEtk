#ifndef NJOY_ACETK_BLOCK_ENERGYDEPENDENTWATTSPECTRUM
#define NJOY_ACETK_BLOCK_ENERGYDEPENDENTWATTSPECTRUM

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/block/ParameterData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief An energy dependent Watt spectrum from the DLW block for a single
 *         reaction
 */
class EnergyDependentWattSpectrum : protected details::Base {

  /* fields */
  ParameterData a_;
  ParameterData b_;

  /* auxiliary functions */
  #include "ACEtk/block/EnergyDependentWattSpectrum/src/verifySize.hpp"
  #include "ACEtk/block/EnergyDependentWattSpectrum/src/generateBlocks.hpp"
  #include "ACEtk/block/EnergyDependentWattSpectrum/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/EnergyDependentWattSpectrum/src/ctor.hpp"

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
