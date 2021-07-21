#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

std::string chunk();
void verifyChunk( const Table& );

SCENARIO( "ContinuousEnergyTable" ){

  GIVEN( "An ACE Table for 92235.710nc" ){
    auto ACETable = Table( njoy::utility::slurpFileToMemory("92235.710nc") );
    WHEN( "constructing a ContinuousEnergyNeutron interpretation" ){

      const auto ncTable = ContinuousEnergyTable( std::move( ACETable ) );

      THEN( "parameters can be extracted" ){

        CHECK( 837481 == ncTable.length() );
        CHECK( 92235 == ncTable.ZA() );
        CHECK( 76518 == ncTable.NES() );
        CHECK( 76518 == ncTable.numberEnergyPoints() );
        CHECK( 48 == ncTable.NTR() );
        CHECK( 48 == ncTable.numberReactionsExcludingElastic() );
        CHECK( 45 == ncTable.NR() );
        CHECK( 45 == ncTable.numberProjectileProductionReactionsExcludingElastic() );
        CHECK( 33 == ncTable.NTRP() );
        CHECK( 33 == ncTable.numberPhotonProductionReactions() );
        CHECK( 0 == ncTable.NTYPE() );
        CHECK( 0 == ncTable.numberAdditionalSecondaryParticleTypes() );
        CHECK( 6 == ncTable.NPCR() );
        CHECK( 6 == ncTable.numberDelayedPrecursors() );
        CHECK( 0 == ncTable.S() );
        CHECK( 0 == ncTable.excitedState() );
        CHECK( 92 == ncTable.Z() );
        CHECK( 92 == ncTable.atomNumber() );
        CHECK( 235 == ncTable.A() );
        CHECK( 235 == ncTable.massNumber() );

        // ESZ block
        CHECK( 76518 == ncTable.ESZ().energies().size() );
        CHECK( 76518 == ncTable.ESZ().total().size() );
        CHECK( 76518 == ncTable.ESZ().disappearance().size() );
        CHECK( 76518 == ncTable.ESZ().elastic().size() );
        CHECK( 76518 == ncTable.ESZ().heating().size() );
      }
    }
  }
}
