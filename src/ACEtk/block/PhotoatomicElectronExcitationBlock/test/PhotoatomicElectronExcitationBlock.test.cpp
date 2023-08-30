#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/PhotoatomicElectronExcitationBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PhotoatomicElectronExcitationBlock = block::PhotoatomicElectronExcitationBlock;

std::vector< double > chunk();
void verifyChunk( const PhotoatomicElectronExcitationBlock& );

SCENARIO( "PhotoatomicElectronExcitationBlock" ) {

  GIVEN( "valid data for a PhotoatomicElectronExcitationBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 10., 20., 200. };
      std::vector< double > loss = { 1., 2., 3. };

      PhotoatomicElectronExcitationBlock chunk( std::move( energies ),
                                                std::move( loss ) );

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

      PhotoatomicElectronExcitationBlock chunk( xss.begin(), xss.end(), 3 );

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

void verifyChunk( const PhotoatomicElectronExcitationBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.length() );
  CHECK( "EXCIT" == chunk.name() );

  CHECK( 3 == chunk.NXL() );
  CHECK( 3 == chunk.numberEnergyPoints() );

  CHECK(  10. == Approx( chunk.energies()[0] ) );
  CHECK(  20. == Approx( chunk.energies()[1] ) );
  CHECK( 200. == Approx( chunk.energies()[2] ) );

  CHECK(   1. == Approx( chunk.excitationEnergyLoss()[0] ) );
  CHECK(   2. == Approx( chunk.excitationEnergyLoss()[1] ) );
  CHECK(   3. == Approx( chunk.excitationEnergyLoss()[2] ) );
}
