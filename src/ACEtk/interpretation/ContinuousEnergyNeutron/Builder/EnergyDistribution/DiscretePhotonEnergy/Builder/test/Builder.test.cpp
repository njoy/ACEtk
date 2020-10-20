#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::DiscretePhotonEnergy::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using DPEBuilder = decltype( parentBuilder.discretePhotonEnergy() );

    struct TestBuilder : public DPEBuilder {
      using DPEBuilder::construct;
      using DPEBuilder::DPEBuilder;
    };

  TestBuilder dPE( parentBuilder );

  GIVEN( "valid inputs" ){
    double energy{ 2.1 };
    int primaryFlag{ 1 };

    dPE.energy( energy )
       .primaryFlag( primaryFlag );

    auto distribution = dPE.construct();

    CHECK_NOTHROW( dPE.primaryFlag( 0 ) );
    CHECK_NOTHROW( dPE.primaryFlag( 2 ) );

    THEN( "the values of the distribution can be checked" ){
      CHECK( energy ==  distribution.energy );
      CHECK( primaryFlag == distribution.primaryFlag );

      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};
        aceified.push_back( primaryFlag );
        aceified.push_back( energy );

        Table::Data data{};
        distribution.ACEify( data, 0 );
        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
    }
  } // GIVEN

  GIVEN( "invalid parameters" ){
    WHEN( "energy is negative" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( dPE.energy( -1.1 ) );
      }
    }
    WHEN( "invalid primary flag values" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( dPE.primaryFlag( -1 ) );
        CHECK_THROWS( dPE.primaryFlag( 3 ) );
      }
    }
    WHEN( "only part of the energy distribution has been built" ){
      GIVEN( "just the primaryFlag" ){
          dPE.primaryFlag( 1 );
          THEN( "an exception is thrown" ){
            CHECK_THROWS_AS( dPE.construct(), std::bad_optional_access& );
          }
        }
      GIVEN( "just the energy" ){
          dPE.energy( 1 );
          THEN( "an exception is thrown" ){
            CHECK_THROWS_AS( dPE.construct(), std::bad_optional_access& );
          }
        }
      }
  }
} // SCENARIO
