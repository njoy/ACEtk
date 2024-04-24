// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/thermal/CrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using CrossSectionBlock = thermal::CrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const CrossSectionBlock& );

SCENARIO( "CrossSectionBlock" ) {

  GIVEN( "valid data for a CrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 10., 20., 30., 40. };
      std::vector< double > xs = { 1., 2., 3., 4. };

      CrossSectionBlock chunk( std::move( energies ),
                                                  std::move( xs ) );

      THEN( "a CrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      CrossSectionBlock chunk( xss.begin(), xss.end() );

      THEN( "a CrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

                     4,  1.00000000000E+01,  2.00000000000E+01,  3.00000000000E+01,
     4.00000000000E+01,  1.00000000000E+00,  2.00000000000E+00,  3.00000000000E+00,
     4.00000000000E+00
  };
}

void verifyChunk( const CrossSectionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 9 == chunk.length() );
  CHECK( "CrossSectionBlock" == chunk.name() );

  CHECK( 4 == chunk.NE() );
  CHECK( 4 == chunk.numberIncidentEnergies() );

  CHECK( 4 == chunk.energies().size() );
  CHECK_THAT( 10., WithinRel( chunk.energies().front() ) );
  CHECK_THAT( 40., WithinRel( chunk.energies().back() ) );

  CHECK( 4 == chunk.crossSections().size() );
  CHECK_THAT( 1., WithinRel( chunk.crossSections().front() ) );
  CHECK_THAT( 4., WithinRel( chunk.crossSections().back() ) );
}
