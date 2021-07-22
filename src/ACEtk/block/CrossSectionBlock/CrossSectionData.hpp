/**
 *  @class
 *  @brief Convenience interface for cross section data from the SIG block
 */
class CrossSectionData : protected Base {

  /* fields */

public:

  /* constructor */
  CrossSectionData( Iterator begin, Iterator end ) :
    Base( "SIGMA", begin, end ) {}

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
};
