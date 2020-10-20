#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::ContinuousTabularDistribution::Builder" ){
  ContinuousEnergyNeutron::Builder CENBuilder;

  auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
  using CTBBuilder = decltype( 
      parentBuilder.continuousTabularDistribution() );

  struct TestBuilder : public CTBBuilder {
    using CTBBuilder::construct;
    using CTBBuilder::CTBBuilder;
  };

  TestBuilder cTB( parentBuilder );

  GIVEN( "valid inputs" ){
    std::vector< int > boundaries{ 1, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0 };

    cTB.boundaries( njoy::utility::copy( boundaries ) )
       .schemes( njoy::utility::copy( schemes ) )
       .energies( njoy::utility::copy( energies ) );

    std::vector< int > INTT{ 1, 2 };
    std::vector< double > ene{ 1.0, 2.0};
    std::vector< double > pdf1{ 0.125, 0.175 };
    std::vector< double > pdf2{ 0.225, 0.275 };
    std::vector< double > cdf1{ 0.125, 1.1 };
    std::vector< double > cdf2{ 0.225, 1.2 };

    cTB.distributionData().interpolationParameter( INTT[ 0 ] )
                          .energies( njoy::utility::copy( ene ) )
                          .pdf( njoy::utility::copy( pdf1 ) )
                          .cdf( njoy::utility::copy( cdf1 ) )
        .add()
       .distributionData().interpolationParameter( INTT[ 1 ] )
                          .energies( njoy::utility::copy( ene ) )
                          .pdf( njoy::utility::copy( pdf2 ) )
                          .cdf( njoy::utility::copy( cdf2 ) )
        .add();

    auto distribution = cTB.construct();

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

      int N_R = boundaries.size();
      int N_E = energies.size();
      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};

        aceified.push_back( N_R );
        aceified |= ranges::action::push_back( boundaries );
        aceified |= ranges::action::push_back( schemes );
        aceified.push_back( N_E );
        aceified |= ranges::action::push_back( energies );
        aceified.push_back( 11 );
        aceified.push_back( 19 );
        // distributionData 1
        aceified.push_back( INTT[ 0 ] );
        aceified.push_back( ene.size() );
        aceified |= ranges::action::push_back( ene ); 
        aceified |= ranges::action::push_back( pdf1 );
        aceified |= ranges::action::push_back( cdf1 );
        // distributionData 2
        aceified.push_back( INTT[ 1 ] );
        aceified.push_back( ene.size() );
        aceified |= ranges::action::push_back( ene ); 
        aceified |= ranges::action::push_back( pdf2 ); 
        aceified |= ranges::action::push_back( cdf2 );

        Table::Data data{};
        distribution.ACEify( data, 0 );

        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
    }
    
  } // GIVEN
  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          cTB.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          cTB.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
  }
} // SCENARIO
