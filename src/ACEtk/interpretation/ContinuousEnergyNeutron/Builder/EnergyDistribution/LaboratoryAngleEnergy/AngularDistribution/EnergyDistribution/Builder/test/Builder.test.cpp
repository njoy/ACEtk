#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( 
  "Testing EnergyDistribtion::LaboratoryAngleEnergy::AngDistribution::"
  "EnergyDistribution::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 )
                                     .energyDistribution()
                                       .laboratoryAngleEnergy()
                                         .angularDistribution();
    using ADBuilder = decltype( parentBuilder.energyDistribution() );

    struct TestBuilder : public ADBuilder {
      using ADBuilder::construct;
      using ADBuilder::ADBuilder;
    };

  TestBuilder engDistribution( parentBuilder );

  GIVEN( "valid inputs" ){
    std::vector< double > ene{ 1.0, 2.0};
    std::vector< double > pdf{ 0.25, 0.75 };
    std::vector< double > cdf{ 0.25, 1.0 };
    std::vector< int > INTEPs{ 1, 2 };

    for( auto INTEP : INTEPs ){
      engDistribution.interpolationParameter( INTEP )
                    .energies( njoy::utility::copy( ene ) )
                    .pdf( njoy::utility::copy( pdf ) )
                    .cdf( njoy::utility::copy( cdf ) );

      auto distribution = engDistribution.construct();
      THEN( "the values can be verified when INTEP = " + 
            std::to_string (INTEP ) ){
        CHECK( INTEP == distribution.interpolationParameter );
        CHECK( ranges::equal( ene, distribution.energies ) );
        CHECK( ranges::equal( pdf, distribution.pdf ) );
        CHECK( ranges::equal( cdf, distribution.cdf ) );
      }
    }
  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          engDistribution.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          engDistribution.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "pdf values are negative" ){
      std::vector< double > pdf{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          engDistribution.pdf( njoy::utility::copy( pdf ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "cdf values are negative" ){
      std::vector< double > cdf{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          engDistribution.cdf( njoy::utility::copy( cdf ) ),
          details::verify::exceptions::InvalidCDF&
        );
      }
    }
    WHEN( "cdf values are not sorted" ){
      std::vector< double > cdf{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          engDistribution.cdf( njoy::utility::copy( cdf ) ),
          details::verify::exceptions::InvalidCDF&
        );
      }
    }
    WHEN( "interpolation parameter is != [1,2] " ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( engDistribution.interpolationParameter( 0 ) );
        CHECK_THROWS( engDistribution.interpolationParameter( 3 ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
