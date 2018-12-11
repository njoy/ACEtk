#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing PhotonProduction::Builder" ){
  GIVEN( "parent builder" ){
    struct Builder : public ContinuousEnergyNeutron::Builder{
      public:
        using ContinuousEnergyNeutron::Builder::PhotonProductionReaction;
    };
    Builder parentBuilder{};

    using PPBuilder = decltype( 
        parentBuilder.photonProductionReaction( 6, 102 ) );

    struct TestBuilder : public PPBuilder {
      using PPBuilder::PPBuilder;
    };
    TestBuilder ppB{ parentBuilder, 6, 102 };
    
    WHEN( "adding a cross section" ){
      bool passed = std::is_same< 
        Builder::PhotonProductionReaction::CrossSection::Builder,
          decltype( ppB.crossSection() ) >::value;
      CHECK( passed );
    }
    WHEN( "adding yields" ){
      bool passed = std::is_same< 
        Builder::PhotonProductionReaction::Yields::Builder,
          decltype( ppB.yields() ) >::value;
      CHECK( passed );
    }
  } // GIVEN
} // SCENARIO
