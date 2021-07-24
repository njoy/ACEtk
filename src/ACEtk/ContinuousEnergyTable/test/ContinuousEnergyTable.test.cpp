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
        CHECK( 48 == ncTable.numberReactions() );
        CHECK( 49 == ncTable.totalNumberReactions() );
        CHECK( 45 == ncTable.NR() );
        CHECK( 45 == ncTable.numberProjectileProductionReactions() );
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

        CHECK( 1e-11 == Approx( ncTable.ESZ().energies().front() ) );
        CHECK( 20. == Approx( ncTable.ESZ().energies().back() ) );

        CHECK( 1e-11 == Approx( ncTable.ESZ().XSS( 1 ) ) );
        CHECK( 76518 == ncTable.ESZ().XSS( 1, ncTable.NES() ).size() );

        // MTR block
        CHECK( 48 == ncTable.MTR().MTs().size() );
        CHECK( 16 == ncTable.MTR().MTs().front() );
        CHECK( 4 == ncTable.MTR().MTs().back() );
        CHECK( 48 == ncTable.MTR().reactionNumbers().size() );
        CHECK( 16 == ncTable.MTR().reactionNumbers().front() );
        CHECK( 4 == ncTable.MTR().reactionNumbers().back() );

        CHECK( 16 == ncTable.MTR().MT( 1 ) );
        CHECK( 4 == ncTable.MTR().MT( 48 ) );
        CHECK( 16 == ncTable.MTR().reactionNumber( 1 ) );
        CHECK( 4 == ncTable.MTR().reactionNumber( 48 ) );

        CHECK( true == ncTable.MTR().hasReactionNumber( 16 ) );
        CHECK( true == ncTable.MTR().hasReactionNumber( 4 ) );
        CHECK( 1 == ncTable.MTR().index( 16 ) );
        CHECK( 48 == ncTable.MTR().index( 4 ) );

        // LQR block
        CHECK( 48 == ncTable.LQR().QValues().size() );
        CHECK( -5.297781 == ncTable.LQR().QValues().front() );
        CHECK( 0. == ncTable.LQR().QValues().back() );

        CHECK( -5.297781 == ncTable.LQR().QValue( 1 ) );
        CHECK( 0. == ncTable.LQR().QValue( 48 ) );

        // TYR block
        CHECK( 48 == ncTable.TYR().referenceFrames().size() );
        CHECK( ReferenceFrame::CentreOfMass == ncTable.TYR().referenceFrames().front() );
        CHECK( ReferenceFrame::Laboratory == ncTable.TYR().referenceFrames().back() );
        CHECK( 48 == ncTable.TYR().multiplicities().size() );
        CHECK( 2 == ncTable.TYR().multiplicities().front() );
        CHECK( 0 == ncTable.TYR().multiplicities().back() );

        CHECK( ReferenceFrame::CentreOfMass == ncTable.TYR().referenceFrame( 1 ) );
        CHECK( ReferenceFrame::Laboratory == ncTable.TYR().referenceFrame( 48 ) );
        CHECK( 2 == ncTable.TYR().multiplicity( 1 ) );
        CHECK( 0 == ncTable.TYR().multiplicity( 48 ) );

        // SIG block
        CHECK( 48 == ncTable.SIG().NTR() );

        CHECK( 1 == ncTable.SIG().LSIG( 1 ) );
        CHECK( 236259 == ncTable.SIG().LSIG( 48 ) );

        CHECK( 76460 == ncTable.SIG().energyIndex( 1 ) );
        CHECK( 76095 == ncTable.SIG().energyIndex( 48 ) );

        CHECK( 59 == ncTable.SIG().numberValues( 1 ) );
        CHECK( 424 == ncTable.SIG().numberValues( 48 ) );

        auto xs1 = ncTable.SIG().crossSectionData( 1 );
        auto xs48 = ncTable.SIG().crossSectionData( 48 );
        CHECK( 76460 == xs1.energyIndex() );
        CHECK( 76095 == xs48.energyIndex() );
        CHECK( 59 == xs1.numberValues() );
        CHECK( 424 == xs48.numberValues() );
        CHECK( 0. == Approx( xs1.crossSections().front() ) );
        CHECK( 1.55512000000E-01 == Approx( xs1.crossSections().back() ) );
        CHECK( 0. == Approx( xs48.crossSections().front() ) );
        CHECK( 3.65016600000E-01 == Approx( xs48.crossSections().back() ) );

        auto data1 = ncTable.SIG().crossSections( 1 );
        auto data48 = ncTable.SIG().crossSections( 48 );
        CHECK( 59 == data1.size() );
        CHECK( 424 == data48.size() );
        CHECK( 0. == Approx( data1.front() ) );
        CHECK( 1.55512000000E-01 == Approx( data1.back() ) );
        CHECK( 0. == Approx( data48.front() ) );
        CHECK( 3.65016600000E-01 == Approx( data48.back() ) );
      }
    }
  }
}
