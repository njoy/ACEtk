#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"
using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing AngularDistribution::Builder::Tabulated::Builder" ){
  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  ParentBuilder parentBuilder{};

  auto angBuilder = parentBuilder.reaction( 22 ).angularDistribution();
  using TabBuilder = decltype( angBuilder.tabulated() );

  struct TestBuilder : public TabBuilder {
    using TabBuilder::construct;
    using TabBuilder::TabBuilder;
  };

  int f{1};
  std::vector< double > cosine{ -0.1, 0.5, 0.8 };
  std::vector< double > pdf{ 0.1, 0.5, 0.4 };
  std::vector< double > cdf{ 0.1, 0.6, 1.0 };

  TestBuilder tb{ angBuilder };
  GIVEN( "valid inputs" ){
    std::vector< int > validFlags{ 0, 1 };

    for( auto f : validFlags ){
      tb.interpolationFlag( f )
          .cosineGrid( njoy::utility::copy( cosine ) )
          .pdf( njoy::utility::copy( pdf ) )
          .cdf( njoy::utility::copy( cdf ) );

      THEN( "the values can be verified when f = " + std::to_string( f ) ){
        auto tabulated = tb.construct();

        CHECK( f == tabulated.interpolationFlag );
        CHECK( ranges::equal( pdf, tabulated.PDF ) );
        CHECK( ranges::equal( cdf, tabulated.CDF ) );
      }
    }
  } // GIVEN
  GIVEN( "invalid inputs" ){
    WHEN( "cosine bins are out of range" ){
      std::vector< double > cosine{ 0.1, 0.5, 1.4 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.cosineGrid( njoy::utility::copy( cosine ) ),
          details::verify::exceptions::InvalidCosine&
        );
      }
    }
    WHEN( "invalid interpolation flags" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( tb.interpolationFlag( -1 ), std::exception& );
        CHECK_THROWS_AS( tb.interpolationFlag(  2 ), std::exception& );
      }
    }
    WHEN( "pdf is invalid" ){
      std::vector< double > pdf{ -0.1, 0.5, 0.4 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.pdf( njoy::utility::copy( pdf ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "cdf is invalid" ){
      std::vector< double > cdf{ 0.1, 0.5, 0.3 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.cdf( njoy::utility::copy( cdf ) ),
          details::verify::exceptions::InvalidCDF&
        );
      }
    }
  } // GIVEN
} // SCENARIO