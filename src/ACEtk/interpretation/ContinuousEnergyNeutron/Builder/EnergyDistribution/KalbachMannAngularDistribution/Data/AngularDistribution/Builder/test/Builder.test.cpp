#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( 
  "Testing EnergyDistribtion::KalbachMann::Data::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 )
                                     .energyDistribution()
                                       .kalbachMannAngularDistribution()
                                         .distributionData();
    using ADBuilder = decltype( parentBuilder.angularDistribution() );

    struct TestBuilder : public ADBuilder {
      using ADBuilder::construct;
      using ADBuilder::ADBuilder;
    };

  TestBuilder angDistribution( parentBuilder );

  int JJ{ 2 };
  std::vector< double > cosines{ -0.99, 0.01, 0.75 };
  std::vector< double > pdf{ 0.25, 0.65, 0.10 };
  std::vector< double > cdf{ 0.25, 0.90, 1.0 };
  GIVEN( "valid inputs" ){

    angDistribution.interpolationParameter( JJ )
                   .cosineGrid( njoy::utility::copy( cosines ) )
                   .pdf( njoy::utility::copy( pdf ) )
                   .cdf( njoy::utility::copy( cdf ) );

    auto distribution = angDistribution.construct();
    THEN( "the values can be verified" ){
      CHECK( JJ == distribution.interpolationParameter );
      CHECK( ranges::equal( cosines, distribution.cosineGrid ) );
      CHECK( ranges::equal( pdf, distribution.pdf ) );
      CHECK( ranges::equal( cdf, distribution.cdf ) );

      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};
        aceified.push_back( JJ );
        aceified.push_back( cosines.size() );
        aceified |= ranges::action::push_back( cosines );
        aceified |= ranges::action::push_back( pdf );
        aceified |= ranges::action::push_back( cdf );

        Table::Data data{};
        distribution.ACEify( data, 0 );

        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
    }
  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "cosines are out of range" ){
      std::vector< double > cosines{ -1.1, 1.1 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          angDistribution.cosineGrid( njoy::utility::copy( cosines ) ),
          details::verify::exceptions::InvalidCosine&
        );
      }
    }
    WHEN( "cosines are not sorted" ){
      std::vector< double > cosines{ -0.75, 0.25, 0.0, 0.75, 0.25 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          angDistribution.cosineGrid( njoy::utility::copy( cosines ) ),
          details::verify::exceptions::InvalidCosine&
        );
      }
    }
    WHEN( "pdf values are negative" ){
      std::vector< double > pdf{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          angDistribution.pdf( njoy::utility::copy( pdf ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "cdf values are negative" ){
      std::vector< double > cdf{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          angDistribution.cdf( njoy::utility::copy( cdf ) ),
          details::verify::exceptions::InvalidCDF&
        );
      }
    }
    WHEN( "cdf values are not sorted" ){
      std::vector< double > cdf{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          angDistribution.cdf( njoy::utility::copy( cdf ) ),
          details::verify::exceptions::InvalidCDF&
        );
      }
    }
    WHEN( "interpolation parameter is <= 0 " ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( angDistribution.interpolationParameter(  0 ) );
        CHECK_THROWS( angDistribution.interpolationParameter( -1 ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
