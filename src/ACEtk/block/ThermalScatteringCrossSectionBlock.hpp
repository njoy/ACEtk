#ifndef NJOY_ACETK_BLOCK_THERMALSCATTERINGCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_THERMALSCATTERINGCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The thermal scattering cross section block
 */
class ThermalScatteringCrossSectionBlock : protected details::ColumnData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/ThermalScatteringCrossSectionBlock/src/ctor.hpp"

  /**
   *  @brief Return the number of energies
   */
  std::size_t NE() const { return this->N(); }

  /**
   *  @brief Return the number of energies
   */
  std::size_t numberEnergies() const { return this->NE(); }

  /**
   *  @brief Return the energies
   */
  auto energies() const { return this->column( 1 ); }

  /**
   *  @brief Return the thermal scattering cross sections
   */
  auto crossSections() const { return this->column( 2 ); }

  using Base::empty;
  using ColumnData::name;
  using ColumnData::length;
  using ColumnData::XSS;
  using ColumnData::begin;
  using ColumnData::end;
};

using ITIE = ThermalScatteringCrossSectionBlock;
using ITCE = ThermalScatteringCrossSectionBlock;
using ITCEI = ThermalScatteringCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
