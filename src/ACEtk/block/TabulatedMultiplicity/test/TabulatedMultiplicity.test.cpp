#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/TabulatedMultiplicity.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedMultiplicity = block::TabulatedMultiplicity;

std::vector< double > chunk();
void verifyChunk( const TabulatedMultiplicity& );

SCENARIO( "TabulatedMultiplicity" ) {

  GIVEN( "valid data for a TabulatedMultiplicity instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > interpolants = {};
      std::vector< long > boundaries = {};
      std::vector< double > energies = { 1., 3., 5. };
      std::vector< double > multiplicities = { 2., 4., 6. };

      TabulatedMultiplicity chunk( std::move( boundaries ),
                                   std::move( interpolants ),
                                   std::move( energies ),
                                   std::move( multiplicities ) );

      THEN( "a TabulatedMultiplicity can be constructed and members can be tested" ) {

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

      TabulatedMultiplicity chunk( xss.begin(), xss.end() );

      THEN( "a TabulatedMultiplicity can be constructed and members can be tested" ) {

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

  return { 0, 3, 1., 3., 5., 2., 4., 6. };
}

void verifyChunk( const TabulatedMultiplicity& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 8 == chunk.length() );
  CHECK( "TabulatedMultiplicity" == chunk.name() );

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
  CHECK( 3 == chunk.numberEnergyPoints() );

  CHECK( 3 == chunk.energies().size() );
  CHECK( 1. == Approx( chunk.energies()[0] ) );
  CHECK( 3. == Approx( chunk.energies()[1] ) );
  CHECK( 5. == Approx( chunk.energies()[2] ) );

  CHECK( 3 == chunk.multiplicities().size() );
  CHECK( 2. == Approx( chunk.multiplicities()[0] ) );
  CHECK( 4. == Approx( chunk.multiplicities()[1] ) );
  CHECK( 6. == Approx( chunk.multiplicities()[2] ) );
}
