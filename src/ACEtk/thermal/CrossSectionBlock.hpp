#ifndef NJOY_ACETK_THERMAL_CROSSSECTIONBLOCK
#define NJOY_ACETK_THERMAL_CROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace thermal {

/**
 *  @class
 *  @brief The thermal scattering cross section block
 */
class CrossSectionBlock : protected base::ColumnData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  CrossSectionBlock() = default;

  CrossSectionBlock( const CrossSectionBlock& ) = default;
  CrossSectionBlock( CrossSectionBlock&& ) = default;

  CrossSectionBlock& operator=( const CrossSectionBlock& ) = default;
  CrossSectionBlock& operator=( CrossSectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energies    the energies
   *  @param[in] xs          the cross section values
   */
  CrossSectionBlock( std::vector< double > energies, std::vector< double > xs ) :
    ColumnData( "CrossSectionBlock",
                std::move( energies ), std::move( xs ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the thermal scattering cross section block
   *  @param[in] end      the end iterator of the thermal scattering cross section block
   */
  CrossSectionBlock( Iterator begin, Iterator end ) :
    ColumnData( "CrossSectionBlock", begin, end, 2 ) {}

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
