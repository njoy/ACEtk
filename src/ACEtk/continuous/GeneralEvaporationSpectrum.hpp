#ifndef NJOY_ACETK_CONTINUOUS_GENERALEVAPORATIONSPECTRUM
#define NJOY_ACETK_CONTINUOUS_GENERALEVAPORATIONSPECTRUM

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/ColumnData.hpp"
#include "ACEtk/base/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief A general evaporation spectrum
 *
 *  The GeneralEvaporationSpectrum class contains the tabulated energy and
 *  temperature values as well as the bin data used to describe the
 *  general evaporation spectrum. It is used in the DLW block as ACE LAW 5.
 */
class GeneralEvaporationSpectrum : protected base::Base {

  /* fields */
  base::TabulatedData tabulated_;
  base::ColumnData bins_;

  /* auxiliary functions */
  #include "ACEtk/continuous/GeneralEvaporationSpectrum/src/verifySize.hpp"
  #include "ACEtk/continuous/GeneralEvaporationSpectrum/src/generateBlocks.hpp"
  #include "ACEtk/continuous/GeneralEvaporationSpectrum/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/GeneralEvaporationSpectrum/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::GeneralEvaporation;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::GeneralEvaporation;
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
   *  @brief Return the number of x values
   */
  int NET() const { return this->bins_.N(); }

  /**
   *  @brief Return the number of equiprobable outgoing x bins
   */
  int numberBins() const { return this->NET() - 1; }

  /**
   *  @brief Return the equiprobable x bins
   */
  auto bins() const { return this->bins_.column( 1 ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ACELAW5 = GeneralEvaporationSpectrum;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
