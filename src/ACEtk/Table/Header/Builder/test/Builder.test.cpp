#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing Table::Header::Builder" ){
  ContinuousEnergyNeutron::Builder parentBuilder;

  using HBuilder = decltype( parentBuilder.header() );
  struct TestBuilder: public HBuilder {
    using HBuilder::construct;
    using HBuilder::HBuilder;
  };

  TestBuilder headBuilder( parentBuilder );

  GIVEN( "valid header data" ){
    double AWR{ 0.9971 };
    double temp{ 293.6 };
    auto pDate = date::year{2019}/3/14;
    std::string szaid{ "1001.123nc" };
    std::string comment1{ "this is comment 1" };
    std::string comment2{ "this is comment 2" };

    headBuilder.processDate( njoy::utility::copy( pDate ) )
               .temperature( temp )
               .atomicWeightRatio( AWR )
               .zaid( szaid )
               .comment( comment1 )
               .comment( comment2 );

    auto header = headBuilder.construct();

    THEN( "the constructed values can be verified" ){
      std::string blank{
        "                                                     " };
      CHECK( AWR == header.atomicWeightRatio );
      CHECK( temp*dimwits::mega( electronVolts ) == header.processTemperature );
      CHECK( pDate == header.processDate );
      CHECK( "              " + szaid == header.szaid );
      CHECK( comment1 + blank == header.comments[0] );
      CHECK( comment2 + blank == header.comments[1] );
    }

  } // GIVEN valid

  GIVEN( "invalid header data" ){
    WHEN( "processed date is bad" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( headBuilder.processDate( 2019, 2, 30 ) );
      }
    }
    WHEN( "atomic weight ratio is negative " ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( headBuilder.atomicWeightRatio( -0.01 ) );
      }
    }
    WHEN( "temperature is negative " ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( headBuilder.temperature( -0.01*dimwits::mega( electronVolts ) ) );
      }
    }
    WHEN( "SZAID is too long" ){
      std::string szaid{ "123456789 123456789 12345" };
      THEN( "an exception is thrown" ){
        CHECK_THROWS( headBuilder.szaid( szaid ) );
      }
    }
    WHEN( "comment is too long" ){
      std::string tooLong{
        "123456789 123456789 123456789 123456789 123456789 123456789 123456789 1"
      };

      THEN( "an exception is thrown" ){
        CHECK_THROWS( headBuilder.comment( tooLong ) );
      }
    }
  } // GIVEN invalid
} // SCEANRIO
