#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing Builder::ProbabilityTable::Builder" ){
  ContinuousEnergyNeutron::Builder parentBuilder{};
  using PTBuilder = decltype( 
      parentBuilder.probabilityTable() );

  struct TestBuilder : public PTBuilder {
    using PTBuilder::construct;
    using PTBuilder::PTBuilder;
  };

  TestBuilder tb{ parentBuilder };

  int INT{ 2 };
  int inelasticCompetition{ 3 };
  int otherAbsorption{ 54 };
  ContinuousEnergyNeutron::Builder::Factors factors{ 
    ContinuousEnergyNeutron::Builder::Factors::CROSSSECTIONS };
  std::vector< double > energies{ 1.0, 2.0, 3.0 };
  std::vector< double > CDFs{ 0.1, 0.4, 1.0 };

  GIVEN( "valid inputs" ){
    std::vector< int > validINTs{ 2, 5 };
    for( auto INT : validINTs ){
      WHEN( "building a probability table with interpolation parameter: " 
            + std::to_string( INT ) ){

        tb.interpolationParameter( INT )
          .inelasticCompetition( inelasticCompetition )
          .otherAbsorption( otherAbsorption )
          .factors( factors )
          .incidentEnergies( njoy::utility::copy( energies ) )
          .CDFs( njoy::utility::copy( CDFs ) );
        auto pTable = tb.construct();

        THEN( "the values can be verified" ){
          CHECK( INT == pTable.interpolationParameter );
          CHECK( inelasticCompetition == pTable.inelasticCompetition );
          CHECK( otherAbsorption == pTable.otherAbsorption );
          CHECK( factors == pTable.factors );
          CHECK( ranges::equal( energies, pTable.incidentEnergies ) );
          CHECK( ranges::equal( CDFs, pTable.CDFs ) );
        }
      }
    }
  } // GIVEN
  GIVEN( "invalid inputs" ){
    WHEN( "incident energies are not all positive" ){
      std::vector< double > energies{ 1.0, -2.0, 3.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.incidentEnergies( energies ),
            details::verify::exceptions::NotPositive& 
        );
      }
    }
    WHEN( "incident energies are not sorted" ){
      std::vector< double > energies{ 1.0, 4.0, 3.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.incidentEnergies( energies ),
            details::verify::exceptions::Unsorted& 
        );
      }
    }
    WHEN( "CDFs are not all positive" ){
      std::vector< double > CDFs{ 0.1, -2.0, 1.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.CDFs( CDFs ),
            details::verify::exceptions::NotPositive& 
        );
      }
    }
    WHEN( "CDFs are not sorted" ){
      std::vector< double > CDFs{ 0.2, 0.1, 1.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.CDFs( CDFs ),
            details::verify::exceptions::Unsorted& 
        );
      }
    }
    WHEN( "CDFs are not the same size as incident energies" ){
      std::vector< double > CDFs{ 0.1, 0.4, 0.6, 1.0 };
      tb.interpolationParameter( INT )
        .inelasticCompetition( inelasticCompetition )
        .otherAbsorption( otherAbsorption )
        .factors( factors )
        .incidentEnergies( njoy::utility::copy( energies ) )
        .CDFs( njoy::utility::copy( CDFs ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.construct(),
            std::range_error&
        );
      }
    }
  }
} // SCENARIO
