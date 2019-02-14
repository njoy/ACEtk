#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::ContinuousTabularDistribution::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 )
                                     .energyDistribution()
                                       .continuousTabularDistribution();
    using DataBuilder = decltype( parentBuilder.distributionData() );

    struct TestBuilder : public DataBuilder {
      using DataBuilder::construct;
      using DataBuilder::DataBuilder;
    };

  TestBuilder dataB( parentBuilder );

  GIVEN( "valid inputs" ){
    int INTT{ 2 };
    std::vector< double > ene{ 1.0, 2.0};
    std::vector< double > pdf{ 0.25, 0.75 };
    std::vector< double > cdf{ 0.25, 1.0 };

    dataB.interpolationParameter( INTT )
         .energies( njoy::utility::copy( ene ) )
         .pdf( njoy::utility::copy( pdf ) )
         .cdf( njoy::utility::copy( cdf ) );
  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          dataB.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          dataB.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "pdf values are negative" ){
      std::vector< double > pdf{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          dataB.pdf( njoy::utility::copy( pdf ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "cdf values are negative" ){
      std::vector< double > cdf{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          dataB.cdf( njoy::utility::copy( cdf ) ),
          details::verify::exceptions::InvalidCDF&
        );
      }
    }
    WHEN( "cdf values are not sorted" ){
      std::vector< double > cdf{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          dataB.cdf( njoy::utility::copy( cdf ) ),
          details::verify::exceptions::InvalidCDF&
        );
      }
    }
    WHEN( "interpolation parameter is <= 0 " ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( dataB.interpolationParameter(  0 ) );
        CHECK_THROWS( dataB.interpolationParameter( -1 ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
