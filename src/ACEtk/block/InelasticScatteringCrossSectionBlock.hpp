#ifndef NJOY_ACETK_BLOCK_INELASTICSCATTERINGCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_INELASTICSCATTERINGCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The inelastic thermal scattering cross section block
 */
class InelasticScatteringCrossSectionBlock : protected details::ColumnData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/InelasticScatteringCrossSectionBlock/src/ctor.hpp"

  /**
   *  @brief Return the number of inelastic energies
   */
  std::size_t NIN() const { return this->N(); }

  /**
   *  @brief Return the number of inelastic energies
   */
  std::size_t numberInelasticEnergies() const { return this->NIN(); }

  /**
   *  @brief Return the inelastic energies
   */
  auto energies() const { return this->column( 1 ); }

  /**
   *  @brief Return the inelastic scattering cross sections
   */
  auto crossSections() const { return this->column( 2 ); }

  using Base::empty;
  using ColumnData::name;
  using ColumnData::length;
  using ColumnData::XSS;
  using ColumnData::begin;
  using ColumnData::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
