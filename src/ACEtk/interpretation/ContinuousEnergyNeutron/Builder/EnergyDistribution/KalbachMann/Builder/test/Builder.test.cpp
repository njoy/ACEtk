#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::KalbachMann::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using KMBuilder = decltype( parentBuilder.kalbachMann() );

    struct TestBuilder : public KMBuilder {
      using KMBuilder::construct;
      using KMBuilder::KMBuilder;
    };

  TestBuilder kM( parentBuilder );

  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0 };
  std::vector< int > INTT{ 1, 2 };
  std::vector< double > ene{ 1.0, 2.0};
  std::vector< double > pdf{ 0.25, 0.75 };
  std::vector< double > cdf{ 0.25, 1.0 };
  std::vector< double > R{ 0.99, 0.01 };
  std::vector< double > A{ 0.75, 0.22 };

  GIVEN( "valid inputs" ){

    kM.boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) );

    kM.distributionData()
        .interpolationParameter( INTT[ 0 ] )
        .energies( njoy::utility::copy( ene ) )
        .pdf( njoy::utility::copy( pdf ) )
        .cdf( njoy::utility::copy( cdf ) )
        .precompoundFraction( njoy::utility::copy( R ) )
        .angularDistributionSlope( njoy::utility::copy( A ) )
      .add() // distributionData
      .distributionData()
        .interpolationParameter( INTT[ 1 ] )
        .energies( njoy::utility::copy( ene ) )
        .pdf( njoy::utility::copy( pdf ) )
        .cdf( njoy::utility::copy( cdf ) )
        .precompoundFraction( njoy::utility::copy( R ) )
        .angularDistributionSlope( njoy::utility::copy( A ) )
      .add();  // distributionData

    auto distribution = kM.construct();

    THEN( "the values can be verified" ){
      auto tab = distribution.tabulated;
      auto parameters = tab.parameters;
      CHECK( ranges::equal( boundaries, parameters->first ) );
      CHECK( ranges::equal( schemes, parameters->second ) );
      CHECK( ranges::equal( energies, tab.x ) );

      auto y = tab.y;
      CHECK( 2 == y.size() );

      int index = 0;
      {
        auto energyDistribution = y[ index ];
        CHECK( INTT[ index ] == energyDistribution.interpolationParameter );
        CHECK( ranges::equal( ene, energyDistribution.energies ) );
        CHECK( ranges::equal( pdf, energyDistribution.pdf ) );
        CHECK( ranges::equal( cdf, energyDistribution.cdf ) );
        CHECK( ranges::equal( R, energyDistribution.precompoundFraction ) );
        CHECK( ranges::equal( A, energyDistribution.angularDistributionSlope ));
      }
      index = 1;
      {
        auto energyDistribution = y[ index ];
        CHECK( INTT[ index ] == energyDistribution.interpolationParameter );
        CHECK( ranges::equal( ene, energyDistribution.energies ) );
        CHECK( ranges::equal( pdf, energyDistribution.pdf ) );
        CHECK( ranges::equal( cdf, energyDistribution.cdf ) );
        CHECK( ranges::equal( R, energyDistribution.precompoundFraction ) );
        CHECK( ranges::equal( A, energyDistribution.angularDistributionSlope ));
      }
      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};

        aceified.push_back( boundaries.size() );
        aceified |= ranges::action::push_back( boundaries );
        aceified |= ranges::action::push_back( schemes );
        aceified.push_back( energies.size() );
        aceified |= ranges::action::push_back( energies );
        aceified.push_back( 11 );
        aceified.push_back( 23 );
        // distributionData 1
        aceified.push_back( INTT[ 0 ] );
        aceified.push_back( ene.size() );
        aceified |= ranges::action::push_back( ene );
        aceified |= ranges::action::push_back( pdf );
        aceified |= ranges::action::push_back( cdf );
        aceified |= ranges::action::push_back( R );
        aceified |= ranges::action::push_back( A );
        // distributionData 2
        aceified.push_back( INTT[ 1 ] );
        aceified.push_back( ene.size() );
        aceified |= ranges::action::push_back( ene );
        aceified |= ranges::action::push_back( pdf );
        aceified |= ranges::action::push_back( cdf );
        aceified |= ranges::action::push_back( R );
        aceified |= ranges::action::push_back( A );

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
          kM.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          kM.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "wrong number of distributionData members" ){
      kM.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .distributionData()
          .interpolationParameter( INTT[ 0 ] )
          .energies( njoy::utility::copy( ene ) )
          .pdf( njoy::utility::copy( pdf ) )
          .cdf( njoy::utility::copy( cdf ) )
          .precompoundFraction( njoy::utility::copy( R ) )
          .angularDistributionSlope( njoy::utility::copy( A ) )
        .add(); // distributionData

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          kM.construct(),
          std::range_error&
        );
      }
    }
  }
} // SCENARIO
