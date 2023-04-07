PolynomialFissionMultiplicity() = default;

PolynomialFissionMultiplicity( const PolynomialFissionMultiplicity& ) = default;
PolynomialFissionMultiplicity( PolynomialFissionMultiplicity&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] coefficients    the polynomial coefficients
 */
PolynomialFissionMultiplicity( std::vector< double > coefficients ) :
  Base( "NU::POLY", generateXSS( std::move( coefficients ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the polynomial representation
 *  @param[in] end      the end iterator of the polynomial representation
 */
PolynomialFissionMultiplicity( Iterator begin, Iterator end ) :
  Base( "NU::POLY", begin, end ) {

  verifySize( this->begin(), this->end(), this->numberCoefficients() );
  verifyLNU( this->type() );
}

PolynomialFissionMultiplicity& operator=( const PolynomialFissionMultiplicity& ) = default;
PolynomialFissionMultiplicity& operator=( PolynomialFissionMultiplicity&& ) = default;
