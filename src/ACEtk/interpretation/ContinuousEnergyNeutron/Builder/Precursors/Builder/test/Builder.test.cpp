#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

template< typename B >
void addEnergyDistribution( B& builder ){
  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };

  std::vector< int > LAWS{ 1, 2, 3, 4, 5, 7, 9, 11 };
  for( auto LAW : LAWS ){
    auto ED = builder.energyDistribution();
    ED.boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .probabilities( njoy::utility::copy( probabilities ) )
      .levelScattering()
        .atomicWeightRatio( 235.98 )
        .QValue( 2.765 )
      .add(); // levelScattering
    ED.add();
  }
}

SCENARIO( "Testing FissionMultiplicity::Precursors::Builder" ){

  ContinuousEnergyNeutron::Builder CENBuilder{};

  using PreBuilder = decltype( CENBuilder.precursors( ) );

  struct TestBuilder : PreBuilder{
    using PreBuilder::construct;
    using PreBuilder::PreBuilder;
  };

  TestBuilder tb{ CENBuilder };

  GIVEN( "valid inputs" ){
    std::vector< double > energies{ 1.0, 2.0 };
    std::vector< double > pdf{ 2.5, 3.7 };
    double l{ 3.14 };

    tb.energies( njoy::utility::copy( energies ) )
      .probabilities( njoy::utility::copy( pdf ) )
      .decayConstant( l );
    addEnergyDistribution( tb );

    auto pre = tb.construct();
    THEN( "the values can be verified" ){

      CHECK( ranges::equal( energies, pre.data.x ) );
      CHECK( ranges::equal( pdf, pre.data.y ) );
      CHECK( l == pre.decayConstant );

      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};
        aceified.push_back( l );
        aceified.push_back( 0 );
        aceified.push_back( energies.size() );
        aceified |= ranges::action::push_back( energies );
        aceified |= ranges::action::push_back( pdf );

        Table::Data data{};
        pre.ACEify( data );

        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
    }
  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "pdf values are negative" ){
      std::vector< double > pdf{ 1.0, -2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.probabilities( njoy::utility::copy( pdf ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "decay constant is negative" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          tb.decayConstant( -0.01 ),
          std::exception&
        );
      }
    }
  } // GIVEN invalid
} // SCENARIO
