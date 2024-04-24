#ifndef NJOY_ACETK_BLOCK_DOSIMETRYCROSSSECTIONDATA
#define NJOY_ACETK_BLOCK_DOSIMETRYCROSSSECTIONDATA

// system includes

// other includes
#include "ACEtk/base/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace dosimetry {

/**
 *  @class
 *  @brief Cross section data from the SIGD block for a single reaction
 *
 *  The CrossSectionData class contains the interpolation regions (if
 *  any are defined) along with the energy and cross section values. The
 *  dosimetry cross sections are different from the other cross section data
 *  blocks in that the data is not given on a common energy grid.
 */
class CrossSectionData : protected base::TabulatedData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/dosimetry/CrossSectionData/src/ctor.hpp"

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return TabulatedData::interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return TabulatedData::NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return TabulatedData::numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return TabulatedData::NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return TabulatedData::boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return TabulatedData::INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return TabulatedData::interpolants(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t NE() const { return TabulatedData::N(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t numberEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return TabulatedData::x(); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const { return TabulatedData::y(); }

  using TabulatedData::empty;
  using TabulatedData::name;
  using TabulatedData::length;
  using TabulatedData::XSS;
  using TabulatedData::begin;
  using TabulatedData::end;
};

} // dosimetry namespace
} // ACEtk namespace
} // njoy namespace

#endif
