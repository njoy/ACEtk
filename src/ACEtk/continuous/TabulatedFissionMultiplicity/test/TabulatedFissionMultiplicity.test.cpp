// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/TabulatedFissionMultiplicity.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedFissionMultiplicity = continuous::TabulatedFissionMultiplicity;

std::vector< double > chunk();
void verifyChunk( const TabulatedFissionMultiplicity&, const std::vector< double >& );
TabulatedFissionMultiplicity makeDummyBlock();

SCENARIO( "TabulatedFissionMultiplicity" ) {

  GIVEN( "valid data for a TabulatedFissionMultiplicity instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 1e-5, 1., 20. };
      std::vector< double > multiplicities = { 2.35, 2.55, 7. };

      TabulatedFissionMultiplicity chunk( std::move( energies ),
                                          std::move( multiplicities ) );

      THEN( "a TabulatedFissionMultiplicity can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      TabulatedFissionMultiplicity chunk( xss.begin(), xss.end() );

      THEN( "a TabulatedFissionMultiplicity can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {                  2,                   0,                   3,
            1.00000000000E-05,   1.00000000000E+00,   2.00000000000E+01,   2.35000000000E+00,
            2.55000000000E+00,   7.00000000000E+00 };
}

void verifyChunk( const TabulatedFissionMultiplicity& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 9 == chunk.length() );
  CHECK( "TabulatedFissionMultiplicity" == chunk.name() );

  CHECK( 2 == chunk.LNU() );
  CHECK( 2 == chunk.type() );

  CHECK( 0 == chunk.interpolationData().NB() );
  CHECK( 0 == chunk.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == chunk.interpolationData().INT().size() );
  CHECK( 0 == chunk.interpolationData().interpolants().size() );
  CHECK( 0 == chunk.interpolationData().NBT().size() );
  CHECK( 0 == chunk.interpolationData().boundaries().size() );

  CHECK( 0 == chunk.NB() );
  CHECK( 0 == chunk.numberInterpolationRegions() );
  CHECK( 0 == chunk.INT().size() );
  CHECK( 0 == chunk.interpolants().size() );
  CHECK( 0 == chunk.NBT().size() );
  CHECK( 0 == chunk.boundaries().size() );

  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberValues() );

  CHECK( 3 == chunk.energies().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 20., WithinRel( chunk.energies()[2] ) );

  CHECK( 3 == chunk.multiplicities().size() );
  CHECK_THAT( 2.35, WithinRel( chunk.multiplicities()[0] ) );
  CHECK_THAT( 2.55, WithinRel( chunk.multiplicities()[1] ) );
  CHECK_THAT( 7., WithinRel( chunk.multiplicities()[2] ) );
}
