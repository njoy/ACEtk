#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( 
    "Testing ContinuousEnergyNeutron::Builder::FissionMultiplicity::Builder" ){
  GIVEN( "parent builder" ){
    struct Builder : public ContinuousEnergyNeutron::Builder{
      public:
        using ContinuousEnergyNeutron::Builder::FissionMultiplicity;
    };
    Builder parentBuilder{};
    using NubarBuilder = decltype( parentBuilder.fissionMultiplicity() );

    struct TestBuilder : NubarBuilder {
      // using NubarBuilder::construct;
      using NubarBuilder::NubarBuilder;
    };

    TestBuilder tb{ parentBuilder };

    THEN( "we can ensure the correct builder is returned" ){
      bool passed = std::is_same< Builder::
          FissionMultiplicity::Polynomial::Builder, 
        decltype( tb.polynomial() ) >::value;
      CHECK( passed );
      passed = std::is_same< Builder::
          FissionMultiplicity::Tabulated::Builder, 
        decltype( tb.tabulated() ) >::value;
      CHECK( passed );
    }
  } // GIVEN
} // SCENARIO
