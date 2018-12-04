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

    std::string nuType{ "total" };
    using NubarBuilder = decltype( 
        parentBuilder.fissionMultiplicity( nuType ) );

    struct TestBuilder : public NubarBuilder {
      using NubarBuilder::NubarBuilder;
    };

    TestBuilder tb{ parentBuilder, "total" };

    WHEN( "creating a polynomial representation" ){
      bool passed = std::is_same< Builder::
          FissionMultiplicity::Polynomial::Builder, 
        decltype( tb.polynomial() ) >::value;
      CHECK( passed );
    }
    WHEN( "creating a tabulated representation" ){
      bool passed = std::is_same< Builder::
          FissionMultiplicity::Tabulated::Builder, 
        decltype( tb.tabulated() ) >::value;
      CHECK( passed );
    }
  } // GIVEN
} // SCENARIO
