#ifndef NJOY_ACETK_CONTINUOUS_SIMPLEMAXWELLIANFISSIONSPECTRUM
#define NJOY_ACETK_CONTINUOUS_SIMPLEMAXWELLIANFISSIONSPECTRUM

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/EvaporationSpectrum.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief A simple Maxwellian fission spectrum
 *
 *  The SimpleMaxwellianFissionSpectrum class contains the tabulated energy and
 *  temperature values as well as the restriction energy U used to describe the
 *  Maxwellian fission spectrum. It is used in the DLW block as ACE LAW 7.
 */
class SimpleMaxwellianFissionSpectrum : protected base::EvaporationSpectrum {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/continuous/SimpleMaxwellianFissionSpectrum/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  EnergyDistributionType LAW() const {

    return EvaporationSpectrum::LAW();
  }

  /**
   *  @brief Return the distribution type
   */
  EnergyDistributionType type() const {

    return EvaporationSpectrum::type();
  }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return EvaporationSpectrum::interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return EvaporationSpectrum::NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return EvaporationSpectrum::numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return EvaporationSpectrum::NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return EvaporationSpectrum::boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return EvaporationSpectrum::INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return EvaporationSpectrum::interpolants(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t NE() const { return EvaporationSpectrum::NE(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t numberEnergyPoints() const {

    return EvaporationSpectrum::numberEnergyPoints();
  }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return EvaporationSpectrum::energies(); }

  /**
   *  @brief Return the temperature values
   */
  auto temperatures() const { return EvaporationSpectrum::temperatures(); }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return EvaporationSpectrum::minimumIncidentEnergy();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return EvaporationSpectrum::maximumIncidentEnergy();
  }

  /**
   *  @brief Return the restriction energy
   */
  double U() const { return EvaporationSpectrum::U(); }

  /**
   *  @brief Return the restriction energy
   */
  double restrictionEnergy() const {

    return EvaporationSpectrum::restrictionEnergy();
  }

  using EvaporationSpectrum::empty;
  using EvaporationSpectrum::name;
  using EvaporationSpectrum::length;
  using EvaporationSpectrum::XSS;
  using EvaporationSpectrum::begin;
  using EvaporationSpectrum::end;
};

using ACELAW7 = SimpleMaxwellianFissionSpectrum;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
