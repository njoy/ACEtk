#ifndef NJOY_ACETK_CONTINUOUS_POLYNOMIALFISSIONMULTIPLICITY
#define NJOY_ACETK_CONTINUOUS_POLYNOMIALFISSIONMULTIPLICITY

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Polynomial fission multiplicity
 *
 *  The PolynomialFissionMultiplicity class contains the polynomial
 *  representation (LNU = 1) of the fission multiplicity. It is
 *  used in the NU block.
 */
class PolynomialFissionMultiplicity : protected base::Base {

  /* fields */

  /* auxiliary functions */

  static std::vector< double > generateXSS(
      std::vector< double >&& coefficients ) {

    std::vector< double > xss = { 1., static_cast< double >( coefficients.size() ) };
    xss.reserve( 2 + coefficients.size() );
    xss.insert( xss.end(), coefficients.begin(), coefficients.end() );

    return xss;
  }

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int numberCoefficients ) {

    auto size = std::distance( begin, end );
    if ( size < numberCoefficients + 2 ) {

      Log::error( "The size of the XSS subrange in the cross section data should "
                  "be at least 2 + XSS(2)" );
      Log::info( "XSS(2) value: {}", numberCoefficients );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  static void verifyLNU( unsigned int LNU ) {

    if ( LNU != 1 ) {

      Log::error( "Expected LNU = XSS(1) = 1 for a polynomial fission multiplicity "
                  "representation" );
      Log::info( "XSS(1) value: {}", LNU );
      throw std::exception();
    }
  }

public:

  /* constructor */

  PolynomialFissionMultiplicity() = default;

  PolynomialFissionMultiplicity( const PolynomialFissionMultiplicity& ) = default;
  PolynomialFissionMultiplicity( PolynomialFissionMultiplicity&& ) = default;

  PolynomialFissionMultiplicity& operator=( const PolynomialFissionMultiplicity& ) = default;
  PolynomialFissionMultiplicity& operator=( PolynomialFissionMultiplicity&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] coefficients    the polynomial coefficients
   */
  PolynomialFissionMultiplicity( std::vector< double > coefficients ) :
    Base( "PolynomialFissionMultiplicity",
          generateXSS( std::move( coefficients ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the polynomial representation
   *  @param[in] end      the end iterator of the polynomial representation
   */
  PolynomialFissionMultiplicity( Iterator begin, Iterator end ) :
    Base( "PolynomialFissionMultiplicity", begin, end ) {

    verifySize( this->begin(), this->end(), this->numberCoefficients() );
    verifyLNU( this->type() );
  }

  /**
   *  @brief Return the representation type (should always be 1)
   */
  unsigned int LNU() const {

    return static_cast< unsigned int >( this->IXSS( 1 ) );
  }

  /**
   *  @brief Return the representation type (should always be 1)
   */
  unsigned int type() const { return this->LNU(); }

  /**
   *  @brief Return the number of polynomial coefficients
   */
  std::size_t NC() const { return this->IXSS( 2 ); }

  /**
   *  @brief Return the number of polynomial coefficients
   */
  std::size_t numberCoefficients() const { return this->NC(); }

  /**
   *  @brief Return the coefficients
   */
  auto C() const {

    return this->XSS( 3, this->numberCoefficients() );
  }

  /**
   *  @brief Return the coefficients
   */
  auto coefficients() const { return this->C(); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
