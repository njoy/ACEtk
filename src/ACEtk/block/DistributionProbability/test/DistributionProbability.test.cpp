#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/DistributionProbability.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using DistributionProbability = block::DistributionProbability;

std::vector< double > chunk();
void verifyChunk( const DistributionProbability& );

SCENARIO( "DistributionProbability" ) {

  GIVEN( "valid data for a DistributionProbability instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > interpolants = {};
      std::vector< long > boundaries = {};
      std::vector< double > energies = { 1., 3., 5. };
      std::vector< double > probabilities = { 2., 4., 6. };

      DistributionProbability chunk( std::move( boundaries ),
                                     std::move( interpolants ),
                                     std::move( energies ),
                                     std::move( probabilities ) );

      THEN( "a DistributionProbability can be constructed and members can be "
            "tested" ) {

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

      DistributionProbability chunk( xss.begin(), xss.end() );

      THEN( "a DistributionProbability can be constructed and members can be "
            "tested" ) {

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

void verifyChunk( const DistributionProbability& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 8 == chunk.length() );
  CHECK( "DLW::DistributionProbability" == chunk.name() );

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

  CHECK( 3 == chunk.probabilities().size() );
  CHECK( 2. == Approx( chunk.probabilities()[0] ) );
  CHECK( 4. == Approx( chunk.probabilities()[1] ) );
  CHECK( 6. == Approx( chunk.probabilities()[2] ) );
}
