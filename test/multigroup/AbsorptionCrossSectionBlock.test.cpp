// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/AbsorptionCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using AbsorptionCrossSectionBlock = multigroup::AbsorptionCrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const AbsorptionCrossSectionBlock&, const std::vector< double >& );

SCENARIO( "AbsorptionCrossSectionBlock" ) {

  GIVEN( "valid data for a AbsorptionCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > absorption = {

  2.384980000000E-03,  2.424430000000E-03,
  2.496190000000E-03,  2.315470000000E-03,  8.409730000000E-04,  4.036970000000E-04,
  1.736890000000E-03,  2.755770000000E-03,  4.859530000000E-03,  8.413150000000E-03,
  1.287110000000E-02,  2.491740000000E-02,  7.386650000000E-02,  1.375860000000E-01,
  1.913170000000E-01,  2.553450000000E-01,  4.572310000000E-01,  8.427400000000E-01,
  1.768620000000E+00,  3.301850000000E+00,  6.219910000000E+00,  1.229650000000E+01,
  2.518970000000E+01,  3.416860000000E+01,  5.801080000000E+01,  1.950920000000E+01,
  4.920370000000E+00,  5.918340000000E+01,  9.898630000000E+02,  2.694230000000E+02
      };
      

      AbsorptionCrossSectionBlock chunk( std::move( absorption ) );

      THEN( "a AbsorptionCrossSectionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      AbsorptionCrossSectionBlock chunk( xss.begin(), xss.end(), 30 );

      THEN( "a AbsorptionCrossSectionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      AbsorptionCrossSectionBlock chunk( xss.begin(), xss.end(), 30 );
      AbsorptionCrossSectionBlock copy( chunk );

      THEN( "an AbsorptionCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      AbsorptionCrossSectionBlock chunk( xss.begin(), xss.end(), 30 );
      AbsorptionCrossSectionBlock move( std::move( chunk ) );

      THEN( "an AbsorptionCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

  2.384980000000E-03,  2.424430000000E-03,
  2.496190000000E-03,  2.315470000000E-03,  8.409730000000E-04,  4.036970000000E-04,
  1.736890000000E-03,  2.755770000000E-03,  4.859530000000E-03,  8.413150000000E-03,
  1.287110000000E-02,  2.491740000000E-02,  7.386650000000E-02,  1.375860000000E-01,
  1.913170000000E-01,  2.553450000000E-01,  4.572310000000E-01,  8.427400000000E-01,
  1.768620000000E+00,  3.301850000000E+00,  6.219910000000E+00,  1.229650000000E+01,
  2.518970000000E+01,  3.416860000000E+01,  5.801080000000E+01,  1.950920000000E+01,
  4.920370000000E+00,  5.918340000000E+01,  9.898630000000E+02,  2.694230000000E+02
  };
}

void verifyChunk( const AbsorptionCrossSectionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 30 == chunk.length() );
  CHECK( "ABS" == chunk.name() );

  CHECK( 30 == chunk.XSS().size() );

  CHECK( 30 == chunk.absorptionCrossSection().size() );

  CHECK_THAT( 2.384980000000E-03, WithinRel( chunk.absorptionCrossSection().front() ) );
  CHECK_THAT( 2.694230000000E+02, WithinRel( chunk.absorptionCrossSection().back() ) );
  CHECK_THAT( 2.384980000000E-03, WithinRel( chunk.SIGABS().front() ) );
  CHECK_THAT( 2.694230000000E+02, WithinRel( chunk.SIGABS().back() ) );
}
