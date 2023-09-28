#ifndef NJOY_ACETK_THERMAL_CROSSSECTIONBLOCK
#define NJOY_ACETK_THERMAL_CROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace thermal {

/**
 *  @class
 *  @brief The thermal scattering cross section block
 */
class CrossSectionBlock : protected block::details::ColumnData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/thermal/CrossSectionBlock/src/ctor.hpp"

  /**
   *  @brief Return the number of energies
   */
  std::size_t NE() const { return this->N(); }

  /**
   *  @brief Return the number of incident energies
   */
  std::size_t numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the incident energies
   */
  auto energies() const { return this->column( 1 ); }

  /**
   *  @brief Return the thermal scattering cross sections
   */
  auto crossSections() const { return this->column( 2 ); }

  using ColumnData::empty;
  using ColumnData::name;
  using ColumnData::length;
  using ColumnData::XSS;
  using ColumnData::begin;
  using ColumnData::end;
};

using ITIE = CrossSectionBlock;
using ITCE = CrossSectionBlock;
using ITCEI = CrossSectionBlock;

} // thermal namespace
} // ACEtk namespace
} // njoy namespace

#endif
