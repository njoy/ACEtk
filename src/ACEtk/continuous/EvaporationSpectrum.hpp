#ifndef NJOY_ACETK_CONTINUOUS_EVAPORATIONSPECTRUM
#define NJOY_ACETK_CONTINUOUS_EVAPORATIONSPECTRUM

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/EvaporationSpectrum.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief An evaporation spectrum
 *
 *  The EvaporationSpectrum class contains the tabulated energy and
 *  temperature values as well as the restriction energy U used to describe the
 *  evaporation spectrum. It is used in the DLW block as ACE LAW 9.
 */
class EvaporationSpectrum : protected base::EvaporationSpectrum {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/continuous/EvaporationSpectrum/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  EnergyDistributionType LAW() const {

    return base::EvaporationSpectrum::LAW();
  }

  /**
   *  @brief Return the distribution type
   */
  EnergyDistributionType type() const {

    return base::EvaporationSpectrum::type();
  }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return base::EvaporationSpectrum::interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return base::EvaporationSpectrum::NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return base::EvaporationSpectrum::numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return base::EvaporationSpectrum::NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return base::EvaporationSpectrum::boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return base::EvaporationSpectrum::INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return base::EvaporationSpectrum::interpolants(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t NE() const { return base::EvaporationSpectrum::NE(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t numberEnergyPoints() const {

    return base::EvaporationSpectrum::numberEnergyPoints();
  }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return base::EvaporationSpectrum::energies(); }

  /**
   *  @brief Return the temperature values
   */
  auto temperatures() const { return base::EvaporationSpectrum::temperatures(); }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return base::EvaporationSpectrum::minimumIncidentEnergy();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return base::EvaporationSpectrum::maximumIncidentEnergy();
  }

  /**
   *  @brief Return the restriction energy
   */
  double U() const { return base::EvaporationSpectrum::U(); }

  /**
   *  @brief Return the restriction energy
   */
  double restrictionEnergy() const {

    return base::EvaporationSpectrum::restrictionEnergy();
  }

  using base::EvaporationSpectrum::empty;
  using base::EvaporationSpectrum::name;
  using base::EvaporationSpectrum::length;
  using base::EvaporationSpectrum::XSS;
  using base::EvaporationSpectrum::begin;
  using base::EvaporationSpectrum::end;
};

using ACELAW9 = EvaporationSpectrum;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
