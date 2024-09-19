// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/PolynomialFissionMultiplicity.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PolynomialFissionMultiplicity = continuous::PolynomialFissionMultiplicity;

std::vector< double > chunk();
void verifyChunk( const PolynomialFissionMultiplicity&, const std::vector< double >& );
PolynomialFissionMultiplicity makeDummyBlock();

SCENARIO( "PolynomialFissionMultiplicity" ) {

  GIVEN( "valid data for a PolynomialFissionMultiplicity instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > coefficients = { 2.5, 1e-8 };

      PolynomialFissionMultiplicity chunk( std::move( coefficients ) );

      THEN( "a PolynomialFissionMultiplicity can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      PolynomialFissionMultiplicity chunk( xss.begin(), xss.end() );

      THEN( "a PolynomialFissionMultiplicity can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 1., 2., 2.5, 1e-8 };
}

void verifyChunk( const PolynomialFissionMultiplicity& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 4 == chunk.length() );
  CHECK( "PolynomialFissionMultiplicity" == chunk.name() );

  CHECK( 4 == chunk.XSS().size() );

  CHECK( 1 == chunk.LNU() );
  CHECK( 1 == chunk.type() );

  CHECK( 2 == chunk.NC() );
  CHECK( 2 == chunk.numberCoefficients() );
  CHECK( 2 == chunk.C().size() );
  CHECK( 2 == chunk.coefficients().size() );

  CHECK_THAT( 2.5, WithinRel( chunk.C().front() ) );
  CHECK_THAT( 1e-8, WithinRel( chunk.C().back() ) );
  CHECK_THAT( 2.5, WithinRel( chunk.coefficients().front() ) );
  CHECK_THAT( 1e-8, WithinRel( chunk.coefficients().back() ) );
}
