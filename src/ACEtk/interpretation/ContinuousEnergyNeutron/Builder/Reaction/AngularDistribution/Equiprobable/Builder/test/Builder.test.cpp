#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"
using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing AngularDistribution::Builder::Tabulated::Builder" ){
  constexpr auto checked = details::hasACEify< ContinuousEnergyNeutron::Builder::Reaction::AngularDistribution::Equiprobable&, double& >::value;
  CHECK( checked );

  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  ParentBuilder parentBuilder{};

  auto angBuilder = parentBuilder.reaction( 22 ).angularDistribution();
  using EquiBuilder = decltype( angBuilder.equiprobableCosineBins() );

  struct TestBuilder : public EquiBuilder {
    using EquiBuilder::construct;
    using EquiBuilder::EquiBuilder;
  };

  std::vector< double > cosineBins{
    0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
    0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
    0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
    0.30, 0.31, 0.32
  };

  TestBuilder tb{ angBuilder };
  GIVEN( "valid inputs" ){
    tb.values( njoy::utility::copy( cosineBins ) );

    THEN( "the constructed values can be verified" ){
      auto equiprobable = tb.construct();

      CHECK( ranges::equal( cosineBins, equiprobable.cosineBins ) );

      AND_THEN( "it can be ACEified" ){
        std::vector< double > aceified{};
        aceified.push_back( 1 );
        aceified |= ranges::action::push_back( cosineBins );

        Table::Data data{};
        data.XSS().push_back( 0 );
        data.JXS()[ 8 ] = 2;
        equiprobable.ACEify( data, data.XSS()[ 0 ] );

        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
    }
  } // GIVEN 
  GIVEN( "invalid inputs" ){
    WHEN( "cosine bins are unsorted" ){
      std::vector< double > cosineBins{
        0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
        0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
        0.20, 0.21, 1.02, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
        0.30, 0.31, 0.32
      };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.values( njoy::utility::copy( cosineBins ) ),
          details::verify::exceptions::InvalidCosine&
        );
      }
    }
    WHEN( "cosine bin values are invalid " ){
      std::vector< double > cosineBins{
        0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
        0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
        0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
        0.30, 0.31, 1.02
      };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.values( njoy::utility::copy( cosineBins ) ),
          details::verify::exceptions::InvalidCosine&
        );
      }
    }
  } // GIVEN 
} // SCENARIO
