#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( 
  "Testing EnergyDistribtion::ContinuousTabularDistribution::Data::Builder" ){
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
    std::vector< double > ene{ 1.0, 2.0};
    std::vector< double > pdf{ 0.25, 0.75 };
    std::vector< double > cdf{ 0.25, 1.0 };

    WHEN( "number of photon lines are given" ){
      int INTT{ 1 };
      int nPhotonLines{ 3 };
      dataB.interpolationParameter( INTT )
           .numberDiscretePhotonLines( nPhotonLines )
           .energies( njoy::utility::copy( ene ) )
           .pdf( njoy::utility::copy( pdf ) )
           .cdf( njoy::utility::copy( cdf ) );
      
      auto distribution = dataB.construct();
      THEN( "the values can be verified" ){
        CHECK( INTT == distribution.interpolationParameter );
        CHECK( ranges::equal( ene, distribution.energies ) );
        CHECK( ranges::equal( pdf, distribution.pdf ) );
        CHECK( ranges::equal( cdf, distribution.cdf ) );
      
        AND_THEN( "the contents can be ACE-ified" ){
          std::vector< double > aceified{};
          aceified.push_back( 31 );
          aceified.push_back( ene.size() );
          aceified |= ranges::action::push_back( ene );
          aceified |= ranges::action::push_back( pdf );
          aceified |= ranges::action::push_back( cdf );
      
          Table::Data data{};
          distribution.ACEify( data, 0 );
          CHECK( ranges::equal( aceified, data.XSS() ) );
        }
      }
    } // WHEN
    WHEN( "number of photon lines are NOT given" ){
      int INTT{ 2 };
      dataB.interpolationParameter( INTT )
           .energies( njoy::utility::copy( ene ) )
           .pdf( njoy::utility::copy( pdf ) )
           .cdf( njoy::utility::copy( cdf ) );
      
      auto distribution = dataB.construct();
      THEN( "the values can be verified" ){
        CHECK( INTT == distribution.interpolationParameter );
        CHECK( ranges::equal( ene, distribution.energies ) );
        CHECK( ranges::equal( pdf, distribution.pdf ) );
        CHECK( ranges::equal( cdf, distribution.cdf ) );
      
        AND_THEN( "the contents can be ACE-ified" ){
          std::vector< double > aceified{};
          aceified.push_back( INTT );
          aceified.push_back( ene.size() );
          aceified |= ranges::action::push_back( ene );
          aceified |= ranges::action::push_back( pdf );
          aceified |= ranges::action::push_back( cdf );
      
          Table::Data data{};
          distribution.ACEify( data, 0 );
          CHECK( ranges::equal( aceified, data.XSS() ) );
        }
      }
    } // WHEN
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
    WHEN( "interpolation parameter is not 1 or 2 " ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( dataB.interpolationParameter( 0 ) );
        CHECK_THROWS( dataB.interpolationParameter( 3 ) );
      }
    }
    WHEN( "number of discrete photon lines is < 0" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( dataB.numberDiscretePhotonLines(  0 ) );
        CHECK_THROWS( dataB.numberDiscretePhotonLines( -1 ) );
      } // THEN
    } // WHEN
  } // GIVEN invalid
} // SCENARIO
