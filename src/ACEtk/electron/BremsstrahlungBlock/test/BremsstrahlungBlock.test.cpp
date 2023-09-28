#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/electron/BremsstrahlungBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using BremsstrahlungBlock = electron::BremsstrahlungBlock;

std::vector< double > chunk();
void verifyChunk( const BremsstrahlungBlock& );

SCENARIO( "BremsstrahlungBlock" ) {

  GIVEN( "valid data for a BremsstrahlungBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 10., 20., 200. };
      std::vector< double > remaining = { 1., 2., 3. };

      BremsstrahlungBlock chunk( std::move( energies ),
                                                    std::move( remaining ) );

      THEN( "a PhotoatomicElectronShellBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      BremsstrahlungBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a PhotoatomicElectronShellBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {  10.,  20., 200.,
             1.,   2.,   3. };
}

void verifyChunk( const BremsstrahlungBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.length() );
  CHECK( "BREML" == chunk.name() );

  CHECK( 3 == chunk.NBL() );
  CHECK( 3 == chunk.numberEnergyPoints() );

  CHECK( 3 == chunk.energies().size() );
  CHECK( 3 == chunk.energyAfterBremsstrahlung().size() );

  CHECK(  10. == Approx( chunk.energies()[0] ) );
  CHECK(  20. == Approx( chunk.energies()[1] ) );
  CHECK( 200. == Approx( chunk.energies()[2] ) );

  CHECK(   1. == Approx( chunk.energyAfterBremsstrahlung()[0] ) );
  CHECK(   2. == Approx( chunk.energyAfterBremsstrahlung()[1] ) );
  CHECK(   3. == Approx( chunk.energyAfterBremsstrahlung()[2] ) );
}
