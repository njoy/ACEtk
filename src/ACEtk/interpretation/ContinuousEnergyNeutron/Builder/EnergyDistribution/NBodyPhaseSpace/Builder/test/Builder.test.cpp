#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::NBodyPhaseSpace::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using NBPSBuilder = decltype( parentBuilder.nBodyPhaseSpace() );

    struct TestBuilder : public NBPSBuilder {
      using NBPSBuilder::construct;
      using NBPSBuilder::NBPSBuilder;
    };

  TestBuilder nBPS( parentBuilder );

  GIVEN( "valid inputs" ){
    int N{ 6 };
    double A{ 14.789 };

    nBPS.numberBodies( N )
        .totalMassRatio( A );

    auto distribution = nBPS.construct();
    THEN( "the values of the distribution can be checked" ){
      CHECK( N == distribution.numberBodies );
      CHECK( A == distribution.totalMassRatio );

      AND_THEN( "the contents can be ACE-ified" ){
        auto aceified = ranges::view::concat( 
          ranges::view::single( N ),
          ranges::view::single( A )
        );

        Table::Data data{};
        distribution.ACEify( data );
        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
    }
  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "number of bodies is negative" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( nBPS.numberBodies( -1 ) );
      }
    }
    WHEN( "total mass ratio is negative" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( nBPS.totalMassRatio( -0.1 ) );
      }
    }
  }
} // GIVEN invalid
