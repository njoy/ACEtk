#ifndef NJOY_ACETK_BLOCK_EVAPORATIONSPECTRUM
#define NJOY_ACETK_BLOCK_EVAPORATIONSPECTRUM

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/block/details/BaseEvaporationSpectrum.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief An evaporation spectrum from the DLW block for a single
 *         reaction
 */
class EvaporationSpectrum : protected details::BaseEvaporationSpectrum {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/EvaporationSpectrum/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  EnergyDistributionType LAW() const {

    return BaseEvaporationSpectrum::LAW();
  }

  /**
   *  @brief Return the distribution type
   */
  EnergyDistributionType type() const {

    return BaseEvaporationSpectrum::type();
  }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return BaseEvaporationSpectrum::interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return BaseEvaporationSpectrum::NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return BaseEvaporationSpectrum::numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return BaseEvaporationSpectrum::NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return BaseEvaporationSpectrum::boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return BaseEvaporationSpectrum::INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return BaseEvaporationSpectrum::interpolants(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t NE() const { return BaseEvaporationSpectrum::NE(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t numberEnergyPoints() const {

    return BaseEvaporationSpectrum::numberEnergyPoints();
  }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return BaseEvaporationSpectrum::energies(); }

  /**
   *  @brief Return the cross section values
   */
  auto temperatures() const { return BaseEvaporationSpectrum::temperatures(); }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return BaseEvaporationSpectrum::minimumIncidentEnergy();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return BaseEvaporationSpectrum::maximumIncidentEnergy();
  }

  /**
   *  @brief Return the restriction energy
   */
  double U() const { return BaseEvaporationSpectrum::U(); }

  /**
   *  @brief Return the restriction energy
   */
  double restrictionEnergy() const {

    return BaseEvaporationSpectrum::restrictionEnergy();
  }

  using BaseEvaporationSpectrum::empty;
  using BaseEvaporationSpectrum::name;
  using BaseEvaporationSpectrum::length;
  using BaseEvaporationSpectrum::XSS;
  using BaseEvaporationSpectrum::begin;
  using BaseEvaporationSpectrum::end;
};

using ACELAW5 = EvaporationSpectrum;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
