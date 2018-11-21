#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;
using namespace dimwits;

SCENARIO( "Constructing UnresolvedResonanceRange::ProbabilityTable" ){
  GIVEN( "valid ProbabilityTable values" ){
    std::vector< double > values{ 0.3, 1.1, 2.1, 3.1, 4.1, 6.1 };

    ContinuousEnergyNeutron::UnresolvedResonanceRange::ProbabilityTable pTable{
      Table::slice( values ) };

    THEN( "the values can be verified" ){
      CHECK( 0.3 == pTable.CDF() );
      CHECK( 1.1 == pTable.totalXS() );
      CHECK( 2.1 == pTable.elasticXS() );
      CHECK( 3.1 == pTable.fissionXS() );
      CHECK( 4.1 == pTable.captureXS() );
      CHECK( 6.1 == pTable.heating() );

      CHECK( 0.3 == pTable.parameter( 1 ) );
      CHECK( 1.1 == pTable.parameter( 2 ) );
      CHECK( 2.1 == pTable.parameter( 3 ) );
      CHECK( 3.1 == pTable.parameter( 4 ) );
      CHECK( 4.1 == pTable.parameter( 5 ) );
      CHECK( 6.1 == pTable.parameter( 6 ) );

    }
  }
} // SCENARIO
