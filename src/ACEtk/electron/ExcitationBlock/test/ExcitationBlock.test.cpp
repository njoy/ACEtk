// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/ExcitationBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ExcitationBlock = electron::ExcitationBlock;

std::vector< double > chunk();
void verifyChunk( const ExcitationBlock&, const std::vector< double >& );
ExcitationBlock makeDummyBlock();

SCENARIO( "ExcitationBlock" ) {

  GIVEN( "valid data for a ExcitationBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 10., 20., 200. };
      std::vector< double > loss = { 1., 2., 3. };

      ExcitationBlock chunk( std::move( energies ),
                                                std::move( loss ) );

      THEN( "a PhotoatomicElectronShellBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      ExcitationBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a PhotoatomicElectronShellBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {  10.,  20., 200.,
             1.,   2.,   3. };
}

void verifyChunk( const ExcitationBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.length() );
  CHECK( "EXCIT" == chunk.name() );

  CHECK( 3 == chunk.NXL() );
  CHECK( 3 == chunk.numberEnergyPoints() );

  CHECK( 3 == chunk.energies().size() );
  CHECK( 3 == chunk.excitationEnergyLoss().size() );

  CHECK_THAT(  10., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT(  20., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 200., WithinRel( chunk.energies()[2] ) );

  CHECK_THAT(   1., WithinRel( chunk.excitationEnergyLoss()[0] ) );
  CHECK_THAT(   2., WithinRel( chunk.excitationEnergyLoss()[1] ) );
  CHECK_THAT(   3., WithinRel( chunk.excitationEnergyLoss()[2] ) );
}
