#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::TabularLinearFunctions::Data::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 )
                                     .energyDistribution()
                                       .tabularLinearFunctions();
    using DataBuilder = decltype( parentBuilder.distributionData() );

    struct TestBuilder : public DataBuilder {
      using DataBuilder::construct;
      using DataBuilder::DataBuilder;
    };

  TestBuilder dataB( parentBuilder );

  GIVEN( "valid inputs" ){
    std::vector< double > P{ 0.1, 0.2, 0.4 };
    std::vector< double > T{ 1.1, 1.2, 1.4 };
    std::vector< double > C{ 2.1, 2.2, 2.4 };

    dataB.P( njoy::utility::copy( P ) )
         .T( njoy::utility::copy( T ) )
         .C( njoy::utility::copy( C ) );

    auto distribution = dataB.construct();

    THEN( "the values can be verified" ){

      CHECK( ranges::equal( P, distribution.P ) );
      CHECK( ranges::equal( T, distribution.T ) );
      CHECK( ranges::equal( C, distribution.C ) );

      AND_THEN( "the contents can be ACE-ified" ){
        auto aceified = ranges::view::concat( P, T, C );

        Table::Data data{};
        distribution.ACEify( data, 0 );
        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
    }
  } // GIVEN valid
} // SCENARIO
