#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::KalbachMannAngularDistribution::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using KMADBuilder = decltype( 
        parentBuilder.kalbachMannAngularDistribution() );

    struct TestBuilder : public KMADBuilder {
      using KMADBuilder::construct;
      using KMADBuilder::KMADBuilder;
    };

  TestBuilder kM( parentBuilder );

  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0 };
  std::vector< int > INTT{ 1, 2 };
  std::vector< double > ene{ 1.0, 2.0};
  std::vector< double > pdf1{ 0.125, 0.175 };
  std::vector< double > pdf2{ 0.225, 0.275 };
  std::vector< double > cdf1{ 0.125, 1.10 };
  std::vector< double > cdf2{ 0.225, 1.20 };
  int JJ{ 2 };
  std::vector< double > cosines{ -0.99, 0.01, 0.75 };
  std::vector< double > apdf{ 0.25, 0.65, 0.10 };
  std::vector< double > acdf{ 0.25, 0.90, 1.0 };

  GIVEN( "valid inputs" ){

    kM.boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .distributionData()
         .interpolationParameter( INTT[ 0 ] )
         .energies( njoy::utility::copy( ene ) )
         .pdf( njoy::utility::copy( pdf1 ) )
         .cdf( njoy::utility::copy( cdf1 ) )
         .angularDistribution()
           .interpolationParameter( JJ )
           .cosineGrid( njoy::utility::copy( cosines ) )
           .pdf( njoy::utility::copy( apdf ) )
           .cdf( njoy::utility::copy( acdf ) )
         .add() // angularDistribution
         .angularDistribution()
           .interpolationParameter( JJ )
           .cosineGrid( njoy::utility::copy( cosines ) )
           .pdf( njoy::utility::copy( apdf ) )
           .cdf( njoy::utility::copy( acdf ) )
         .add()  // angularDistribution
      .add() // distributionData
      .distributionData()
         .interpolationParameter( INTT[ 1 ] )
         .energies( njoy::utility::copy( ene ) )
         .pdf( njoy::utility::copy( pdf2 ) )
         .cdf( njoy::utility::copy( cdf2 ) )
         .angularDistribution()
           .interpolationParameter( JJ )
           .cosineGrid( njoy::utility::copy( cosines ) )
           .pdf( njoy::utility::copy( apdf ) )
           .cdf( njoy::utility::copy( acdf ) )
         .add() // angularDistribution
         .angularDistribution()
           .interpolationParameter( JJ )
           .cosineGrid( njoy::utility::copy( cosines ) )
           .pdf( njoy::utility::copy( apdf ) )
           .cdf( njoy::utility::copy( acdf ) )
         .add()  // angularDistribution
       .add(); // distributionData

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
        CHECK( ranges::equal( pdf1, energyDistribution.pdf ) );
        CHECK( ranges::equal( cdf1, energyDistribution.cdf ) );
      }
      index = 1;
      {
        auto energyDistribution = y[ index ];
        CHECK( INTT[ index ] == energyDistribution.interpolationParameter );
        CHECK( ranges::equal( ene, energyDistribution.energies ) );
        CHECK( ranges::equal( pdf2, energyDistribution.pdf ) );
        CHECK( ranges::equal( cdf2, energyDistribution.cdf ) );
      }

      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};

        aceified.push_back( boundaries.size() );
        aceified |= ranges::action::push_back( boundaries );
        aceified |= ranges::action::push_back( schemes );
        aceified.push_back( energies.size() );
        aceified |= ranges::action::push_back( energies );
        aceified.push_back( 11 );
        aceified.push_back( 43 );
        // distributionData---size 32
        aceified.push_back( INTT[ 0 ] );
        aceified.push_back( ene.size() );
        aceified |= ranges::action::push_back( ene );
        aceified |= ranges::action::push_back( pdf1 );
        aceified |= ranges::action::push_back( cdf1 );
        aceified.push_back( 21 );
        aceified.push_back( 32 );
          // angularDistrubtion---size 11
          aceified.push_back( JJ );
          aceified.push_back( cosines.size() );
          aceified |= ranges::action::push_back( cosines );
          aceified |= ranges::action::push_back( apdf );
          aceified |= ranges::action::push_back( acdf );
          // angularDistrubtion---size 11
          aceified.push_back( JJ );
          aceified.push_back( cosines.size() );
          aceified |= ranges::action::push_back( cosines );
          aceified |= ranges::action::push_back( apdf );
          aceified |= ranges::action::push_back( acdf );
        // distributionData---size32
        aceified.push_back( INTT[ 1 ] );
        aceified.push_back( ene.size() );
        aceified |= ranges::action::push_back( ene );
        aceified |= ranges::action::push_back( pdf2 );
        aceified |= ranges::action::push_back( cdf2 );
        aceified.push_back( 53 );
        aceified.push_back( 64 );
          // angularDistrubtion---size 11
          aceified.push_back( JJ );
          aceified.push_back( cosines.size() );
          aceified |= ranges::action::push_back( cosines );
          aceified |= ranges::action::push_back( apdf );
          aceified |= ranges::action::push_back( acdf );
          // angularDistrubtion---size 11
          aceified.push_back( JJ );
          aceified.push_back( cosines.size() );
          aceified |= ranges::action::push_back( cosines );
          aceified |= ranges::action::push_back( apdf );
          aceified |= ranges::action::push_back( acdf );

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
          .pdf( njoy::utility::copy( pdf1 ) )
          .cdf( njoy::utility::copy( cdf1 ) )
          .angularDistribution()
            .interpolationParameter( JJ )
            .cosineGrid( njoy::utility::copy( cosines ) )
            .pdf( njoy::utility::copy( apdf ) )
            .cdf( njoy::utility::copy( acdf ) )
          .add() // angularDistribution
          .angularDistribution()
            .interpolationParameter( JJ )
            .cosineGrid( njoy::utility::copy( cosines ) )
            .pdf( njoy::utility::copy( apdf ) )
            .cdf( njoy::utility::copy( acdf ) )
          .add()  // angularDistribution
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
