/**
 *  @class
 *  @brief Cross section data from the SIG block for a single reaction
 *
 *  The CrossSectionData class contains the index of the energy point
 *  corresponding to the first cross section value, the number of cross
 *  section values and the actual cross section values.
 */
class CrossSectionData : protected Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/CrossSectionBlock/CrossSectionData/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/CrossSectionBlock/CrossSectionData/src/ctor.hpp"

  /**
   *  @brief Return the energy index
   */
  std::size_t energyIndex() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of cross section values
   */
  std::size_t numberValues() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const {

    return this->XSS( 3, this->numberValues() );
  }

  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};
