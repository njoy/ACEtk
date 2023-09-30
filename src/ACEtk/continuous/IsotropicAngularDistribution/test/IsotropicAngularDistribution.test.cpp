#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/IsotropicAngularDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using IsotropicAngularDistribution = continuous::IsotropicAngularDistribution;

void verifyChunk( const IsotropicAngularDistribution& );

SCENARIO( "IsotropicAngularDistribution" ) {

  GIVEN( "valid data for a IsotropicAngularDistribution instance" ) {

    WHEN( "the data is given explicitly" ) {

      double energy = 2.1;

      IsotropicAngularDistribution chunk( energy );

      THEN( "a IsotropicAngularDistribution can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const IsotropicAngularDistribution& chunk ) {

  CHECK( 2.1 == Approx( chunk.energy() ) );
}
