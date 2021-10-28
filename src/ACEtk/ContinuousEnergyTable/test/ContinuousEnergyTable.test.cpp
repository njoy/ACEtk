#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using AngularDistributionData = block::AngularDistributionData;
using FullyIsotropicDistribution = block::FullyIsotropicDistribution;
using DistributionGivenElsewhere = block::DistributionGivenElsewhere;
using LevelScatteringDistribution = block::LevelScatteringDistribution;
using KalbachMannDistributionData = block::KalbachMannDistributionData;

std::string chunk();
void verifyChunk( const Table& );

SCENARIO( "ContinuousEnergyTable" ){

  GIVEN( "An ACE Table for 92235.710nc" ){
    auto ACETable = Table( njoy::utility::slurpFileToMemory("92235.710nc") );
    WHEN( "constructing a ContinuousEnergyNeutron interpretation" ){

      const auto ncTable = ContinuousEnergyTable( std::move( ACETable ) );

      THEN( "parameters can be extracted" ){

        CHECK( "92235.80c" == ncTable.ZAID() );
        CHECK( 2.5301e-8 == Approx( ncTable.temperature() ) );

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
        CHECK( false == ncTable.ESZ().empty() );
        CHECK( 76518 == ncTable.ESZ().energies().size() );
        CHECK( 76518 == ncTable.ESZ().total().size() );
        CHECK( 76518 == ncTable.ESZ().disappearance().size() );
        CHECK( 76518 == ncTable.ESZ().elastic().size() );
        CHECK( 76518 == ncTable.ESZ().heating().size() );

        CHECK( 1e-11 == Approx( ncTable.ESZ().energies().front() ) );
        CHECK( 20. == Approx( ncTable.ESZ().energies().back() ) );

        CHECK( 1e-11 == Approx( ncTable.ESZ().XSS( 1 ) ) );
        CHECK( 76518 == ncTable.ESZ().XSS( 1, ncTable.NES() ).size() );

        // NU block
        CHECK( false == ncTable.NU().empty() );

        CHECK( true == ncTable.NU().hasPromptAndTotalFissionMultiplicity() );

        auto prompt = std::get< njoy::ACEtk::block::TabulatedFissionMultiplicity >( ncTable.NU().promptFissionMultiplicity() );
        auto total = std::get< njoy::ACEtk::block::TabulatedFissionMultiplicity >( ncTable.NU().totalFissionMultiplicity() );

        CHECK( 0 == prompt.NB() );
        CHECK( 79 == prompt.NE() );
        CHECK( 1e-11 == Approx( prompt.energies().front() ) );
        CHECK( 20. == Approx( prompt.energies().back() ) );
        CHECK( 2.42085 == Approx( prompt.multiplicities().front() ) );
        CHECK( 5.200845 == Approx( prompt.multiplicities().back() ) );

        CHECK( 0 == total.NB() );
        CHECK( 79 == total.NE() );
        CHECK( 1e-11 == Approx( total.energies().front() ) );
        CHECK( 20. == Approx( total.energies().back() ) );
        CHECK( 2.4367 == Approx( total.multiplicities().front() ) );
        CHECK( 5.209845 == Approx( total.multiplicities().back() ) );

        // MTR block
        CHECK( false == ncTable.MTR().empty() );
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
        CHECK( false == ncTable.LQR().empty() );
        CHECK( 48 == ncTable.LQR().QValues().size() );
        CHECK( -5.297781 == ncTable.LQR().QValues().front() );
        CHECK( 0. == ncTable.LQR().QValues().back() );

        CHECK( -5.297781 == ncTable.LQR().QValue( 1 ) );
        CHECK( 0. == ncTable.LQR().QValue( 48 ) );

        // TYR block
        CHECK( false == ncTable.TYR().empty() );
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
        CHECK( false == ncTable.SIG().empty() );
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

        // AND block
        CHECK( false == ncTable.AND().empty() );
        CHECK( 45 == ncTable.AND().NR() );

        CHECK( 1 == ncTable.AND().LAND( 0 ) ); // elastic
        CHECK( 0 == ncTable.AND().LAND( 3 ) );
        CHECK( 63802 == ncTable.AND().LAND( 44 ) );
        CHECK( -1 == ncTable.AND().LAND( 45 ) );

        CHECK( true == std::holds_alternative< AngularDistributionData >( ncTable.AND().angularDistributionData( 0 ) ) ); // elastic
        CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( ncTable.AND().angularDistributionData( 3 ) ) );
        CHECK( true == std::holds_alternative< AngularDistributionData >( ncTable.AND().angularDistributionData( 44 ) ) );
        CHECK( true == std::holds_alternative< DistributionGivenElsewhere >( ncTable.AND().angularDistributionData( 45 ) ) );

        // DLW block
        CHECK( false == ncTable.DLW().empty() );
        CHECK( 45 == ncTable.DLW().NR() );

        CHECK( 1 == ncTable.DLW().LDLW( 1 ) );
        CHECK( 48133 == ncTable.DLW().LDLW( 44 ) );
        CHECK( 48144 == ncTable.DLW().LDLW( 45 ) );

        CHECK( true == std::holds_alternative< KalbachMannDistributionData >( ncTable.DLW().energyDistributionData( 1 ) ) );
        CHECK( true == std::holds_alternative< LevelScatteringDistribution >( ncTable.DLW().energyDistributionData( 44 ) ) );
        CHECK( true == std::holds_alternative< KalbachMannDistributionData >( ncTable.DLW().energyDistributionData( 45 ) ) );
      }
    }
  }
}
