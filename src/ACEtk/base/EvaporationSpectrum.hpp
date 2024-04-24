#ifndef NJOY_ACETK_BASE_EVAPORATIONSPECTRUM
#define NJOY_ACETK_BASE_EVAPORATIONSPECTRUM

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief A general evaporation spectrum from the DLW block for a single
 *         reaction
 */
class EvaporationSpectrum : protected Base {

  /* fields */
  TabulatedData tabulated_;
  EnergyDistributionType type_;

  /* auxiliary functions */
  #include "ACEtk/base/EvaporationSpectrum/src/verifySize.hpp"
  #include "ACEtk/base/EvaporationSpectrum/src/generateBlocks.hpp"
  #include "ACEtk/base/EvaporationSpectrum/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/base/EvaporationSpectrum/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  EnergyDistributionType LAW() const {

    return this->type_;
  }

  /**
   *  @brief Return the distribution type
   */
  EnergyDistributionType type() const {

    return this->LAW();
  }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return this->tabulated_.interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return this->tabulated_.NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return this->tabulated_.numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return this->tabulated_.NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return this->tabulated_.boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return this->tabulated_.INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->tabulated_.interpolants(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t NE() const { return this->tabulated_.N(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t numberEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->tabulated_.x(); }

  /**
   *  @brief Return the cross section values
   */
  auto temperatures() const { return this->tabulated_.y(); }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return this->energies().front();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return this->energies().back();
  }

  /**
   *  @brief Return the restriction energy
   */
  double U() const { return *this->tabulated_.end(); }

  /**
   *  @brief Return the restriction energy
   */
  double restrictionEnergy() const { return this->U(); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::IXSS;
  using Base::begin;
  using Base::end;
};

} // base namespace
} // ACEtk namespace
} // njoy namespace

#endif
