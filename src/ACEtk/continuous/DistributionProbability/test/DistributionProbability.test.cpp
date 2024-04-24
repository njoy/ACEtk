// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/DistributionProbability.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using DistributionProbability = continuous::DistributionProbability;

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

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
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

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
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
  CHECK( "DistributionProbability" == chunk.name() );

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
  CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 5., WithinRel( chunk.energies()[2] ) );

  CHECK( 3 == chunk.probabilities().size() );
  CHECK_THAT( 2., WithinRel( chunk.probabilities()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.probabilities()[1] ) );
  CHECK_THAT( 6., WithinRel( chunk.probabilities()[2] ) );
}
