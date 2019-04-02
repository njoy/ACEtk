#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( 
  "Testing EnergyDistribtion::LaboratoryAngleEnergy::AngularDistribution::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 )
                                     .energyDistribution()
                                       .laboratoryAngleEnergy();
    using ADBuilder = decltype( parentBuilder.angularDistribution() );

    struct TestBuilder : public ADBuilder {
      using ADBuilder::construct;
      using ADBuilder::ADBuilder;
    };

  TestBuilder ad( parentBuilder );

  GIVEN( "valid inputs" ){
    std::vector< double > cosines{ -0.99, 0.01, 0.75 };
    std::vector< int > INTMUs{ 1, 2 };

    std::vector< double > ene{ 1.0, 2.0};
    std::vector< double > pdf{ 0.25, 0.75 };
    std::vector< double > cdf{ 0.25, 1.0 };
    std::vector< int > INTEPs{ 1, 2 };

    for( auto INTMU : INTMUs ){
      ad.interpolationParameter( INTMU )
        .cosines( njoy::utility::copy( cosines ) )
        .energyDistribution()
          .interpolationParameter( INTEPs[ 0 ] )
          .energies( njoy::utility::copy( ene ) )
          .pdf( njoy::utility::copy( pdf ) )
          .cdf( njoy::utility::copy( cdf ) )
        .add() // energyDistribution
        .energyDistribution()
          .interpolationParameter( INTEPs[ 1 ] )
          .energies( njoy::utility::copy( ene ) )
          .pdf( njoy::utility::copy( pdf ) )
          .cdf( njoy::utility::copy( cdf ) )
        .add() // energyDistribution
        .energyDistribution()
          .interpolationParameter( INTEPs[ 0 ] )
          .energies( njoy::utility::copy( ene ) )
          .pdf( njoy::utility::copy( pdf ) )
          .cdf( njoy::utility::copy( cdf ) )
        .add(); // energyDistribution

      auto distribution = ad.construct();
      THEN( "the values can be verified when INTMU = " + 
            std::to_string (INTMU ) ){
        CHECK( INTMU == distribution.interpolationParameter );
        CHECK( ranges::equal( cosines, distribution.cosines ) );

        AND_THEN( "the contents can be ACE-ified" ){
          auto aceified = ranges::view::concat( 
            ranges::view::single( INTMU ),
            ranges::view::single( cosines.size() ),
            cosines,
            ranges::view::single( 9 ),
            ranges::view::single( 17 ),
            ranges::view::single( 25 ),
            // energyDistribution---size 8
            ranges::view::single( INTEPs[ 0 ] ),
            ranges::view::single( ene.size() ),
            ene, pdf, cdf,
            // energyDistribution---size 8
            ranges::view::single( INTEPs[ 1 ] ),
            ranges::view::single( ene.size() ),
            ene, pdf, cdf,
            // energyDistribution---size 8
            ranges::view::single( INTEPs[ 0 ] ),
            ranges::view::single( ene.size() ),
            ene, pdf, cdf

          );

          Table::Data data{};
          distribution.ACEify( data, 0 );

          CHECK( ranges::equal( aceified, data.XSS() ) );
        }
      }
    }

  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "cosines are out of range" ){
      std::vector< double > cosines{ -1.1, 1.1 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          ad.cosines( njoy::utility::copy( cosines ) ),
          details::verify::exceptions::InvalidCosine&
        );
      }
    }
    WHEN( "cosines are not sorted" ){
      std::vector< double > cosines{ -0.75, 0.25, 0.0, 0.75, 0.25 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          ad.cosines( njoy::utility::copy( cosines ) ),
          details::verify::exceptions::InvalidCosine&
        );
      }
    }
    WHEN( "interpolation parameter is != [1,2] " ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( ad.interpolationParameter( 0 ) );
        CHECK_THROWS( ad.interpolationParameter( 3 ) );
      }
    }
  }
} // SCENARIO
