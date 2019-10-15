#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::TabularLinearMultipliers::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using LAW24Builder = decltype( parentBuilder.tabularEnergyMultipliers() );

    struct TestBuilder : public LAW24Builder {
      using LAW24Builder::construct;
      using LAW24Builder::LAW24Builder;
    };


  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > T1{ 1.1, 1.2, 1.3 };
  std::array< double, 3 > T2{{ 1.1, 1.2, 1.4 }};

  TestBuilder law24( parentBuilder );

  GIVEN( "valid inputs" ){

    law24.boundaries( njoy::utility::copy( boundaries ) )
         .schemes( njoy::utility::copy( schemes ) )
         .energies( njoy::utility::copy( energies ) )
         .table( njoy::utility::copy( T1 ) )
         .table( njoy::utility::copy( T1 ) )
         .table( njoy::utility::copy( T2 ) )
         .table( njoy::utility::copy( T2 ) );

      auto distribution = law24.construct();
      THEN( "the values can be verified" ){
        auto parameters = distribution.parameters;
        CHECK( ranges::equal( boundaries, parameters->first ) );
        CHECK( ranges::equal( schemes, parameters->second ) );
        CHECK( ranges::equal( energies, distribution.x ) );

        auto y = distribution.y;
        CHECK( ranges::equal( T1, y[0] ) );
        CHECK( ranges::equal( T1, y[1] ) );
        CHECK( ranges::equal( T2, y[2] ) );
        CHECK( ranges::equal( T2, y[3] ) );

      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};
        aceified.push_back( boundaries.size() );
        aceified |= ranges::action::push_back( boundaries );
        aceified |= ranges::action::push_back( schemes );
        aceified.push_back( energies.size() );
        aceified |= ranges::action::push_back( energies );
        aceified.push_back( T1.size() );
        aceified |= ranges::action::push_back( T1 );
        aceified |= ranges::action::push_back( T1 );
        aceified |= ranges::action::push_back( T2 );
        aceified |= ranges::action::push_back( T2 );

        Table::Data data{};
        distribution.ACEify( data, 0 );

        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
      }

  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          law24.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          law24.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "wrong number of tables are given" ){
      law24.boundaries( njoy::utility::copy( boundaries ) )
           .schemes( njoy::utility::copy( schemes ) )
           .energies( njoy::utility::copy( energies ) )
           .table( njoy::utility::copy( T1 ) )
           .table( njoy::utility::copy( T1 ) )
           .table( njoy::utility::copy( T2 ) );

      THEN( "an exception is thrown" ){
        CHECK_THROWS( law24.construct() );
      }
      
      law24.table( njoy::utility::copy( T2 ) )
           .table( njoy::utility::copy( T2 ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS( law24.construct() );
      }
    }
    WHEN( "table sizes are different" ){
      std::vector< double > T3{ 1.1, 1.2, 1.3, 1.4 };
      law24.table( njoy::utility::copy( T2 ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS( law24.table( njoy::utility::copy( T3 ) ) );
      }
    }
  }
} // SCENARIO
