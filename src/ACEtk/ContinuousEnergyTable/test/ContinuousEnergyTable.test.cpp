// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/ContinuousEnergyTable.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::ACEtk;
using AngularDistributionData = continuous::AngularDistributionData;
using FullyIsotropicDistribution = continuous::FullyIsotropicDistribution;
using DistributionGivenElsewhere = continuous::DistributionGivenElsewhere;
using LevelScatteringDistribution = continuous::LevelScatteringDistribution;
using KalbachMannDistributionData = continuous::KalbachMannDistributionData;
using DiscretePhotonDistribution = continuous::DiscretePhotonDistribution;
using OutgoingEnergyDistributionData = continuous::OutgoingEnergyDistributionData;
using PhotonProductionCrossSectionData = continuous::PhotonProductionCrossSectionData;
using TabulatedSecondaryParticleMultiplicity = continuous::TabulatedSecondaryParticleMultiplicity;
using TwoBodyTransferDistribution = continuous::TwoBodyTransferDistribution;

void verifyChunkU235( const ContinuousEnergyTable& );
void verifyChunkHe3( const ContinuousEnergyTable& );
void verifyChunkNJOY99U238( const ContinuousEnergyTable& );

SCENARIO( "ContinuousEnergyTable" ) {

  GIVEN( "valid data for a ContinuousEnergyTable - U235" ) {

    auto table = fromFile( "92235.710nc" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a ContinuousEnergyTable from a table" ) {

      ContinuousEnergyTable chunk( std::move( table ) );

      THEN( "a ContinuousEnergyTable can be constructed and members can be "
            "tested" ) {

        verifyChunkU235( chunk );
      }

      THEN( "the IZ array is correct" ) {

        decltype(auto) iz_chunk = chunk.data().IZ();
        CHECK( iz.size() == iz_chunk.size() );
        for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {

          CHECK( iz[i] == iz_chunk[i] );
        }
      } // THEN

      THEN( "the AW array is correct" ) {

        decltype(auto) aw_chunk = chunk.data().AW();
        CHECK( aw.size() == aw_chunk.size() );
        for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {

          CHECK_THAT( aw[i], WithinRel( aw_chunk[i] ) );
        }
      } // THEN

      THEN( "the NXS array is correct" ) {

        decltype(auto) nxs_chunk = chunk.data().NXS();
        CHECK( nxs.size() == nxs_chunk.size() );
        for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {

          CHECK( nxs[i] == nxs_chunk[i] );
        }
      } // THEN

      THEN( "the JXS array is correct" ) {

        decltype(auto) jxs_chunk = chunk.data().JXS();
        CHECK( jxs.size() == jxs_chunk.size() );
        for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {

          CHECK( jxs[i] == jxs_chunk[i] );
        }
      } // THEN

      THEN( "the XSS array is correct" ) {

        decltype(auto) xss_chunk = chunk.data().XSS();
        CHECK( xss.size() == xss_chunk.size() );
        for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "constructing a ContinuousEnergyTable from its components" ) {

      ContinuousEnergyTable base( std::move( table ) );

      ContinuousEnergyTable chunk( 92, 235, 0, base.header(),
                                   base.ESZ(), base.NU(), base.DNU(),
                                   base.MTR(), base.LQR(),
                                   base.SIG(), base.AND(), base.DLW(),
                                   base.BDD(), base.DNED(),
                                   base.GPD(), base.MTRP(), base.SIGP(),
                                   base.ANDP(), base.DLWP(), base.YP(),
                                   base.UNR(),
                                   std::nullopt, std::nullopt, std::nullopt,
                                   std::nullopt, std::nullopt, std::nullopt,
                                   std::nullopt );

      THEN( "a ContinuousEnergyTable can be constructed and members can be "
            "tested" ) {

        verifyChunkU235( chunk );
      }

      THEN( "the IZ array is correct" ) {

        decltype(auto) iz_chunk = chunk.data().IZ();
        CHECK( iz.size() == iz_chunk.size() );
        for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {

          CHECK( iz[i] == iz_chunk[i] );
        }
      } // THEN

      THEN( "the AW array is correct" ) {

        decltype(auto) aw_chunk = chunk.data().AW();
        CHECK( aw.size() == aw_chunk.size() );
        for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {

          CHECK_THAT( aw[i], WithinRel( aw_chunk[i] ) );
        }
      } // THEN

      THEN( "the NXS array is correct" ) {

        decltype(auto) nxs_chunk = chunk.data().NXS();
        CHECK( nxs.size() == nxs_chunk.size() );
        for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {

          CHECK( nxs[i] == nxs_chunk[i] );
        }
      } // THEN

      THEN( "the JXS array is correct" ) {

        decltype(auto) jxs_chunk = chunk.data().JXS();
        CHECK( jxs.size() == jxs_chunk.size() );
        for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {

          CHECK( jxs[i] == jxs_chunk[i] );
        }
      } // THEN

      THEN( "the XSS array is correct" ) {

        decltype(auto) xss_chunk = chunk.data().XSS();
        CHECK( xss.size() == xss_chunk.size() );
        for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ContinuousEnergyTable - He3" ) {

    auto table = fromFile( "2003.710nc" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a ContinuousEnergyTable from a table" ) {

      ContinuousEnergyTable chunk( std::move( table ) );

      THEN( "a ContinuousEnergyTable can be constructed and members can be tested" ) {

        verifyChunkHe3( chunk );
      }

      THEN( "the IZ array is correct" ) {

        decltype(auto) iz_chunk = chunk.data().IZ();
        CHECK( iz.size() == iz_chunk.size() );
        for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {

          CHECK( iz[i] == iz_chunk[i] );
        }
      } // THEN

      THEN( "the AW array is correct" ) {

        decltype(auto) aw_chunk = chunk.data().AW();
        CHECK( aw.size() == aw_chunk.size() );
        for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {

          CHECK_THAT( aw[i], WithinRel( aw_chunk[i] ) );
        }
      } // THEN

      THEN( "the NXS array is correct" ) {

        decltype(auto) nxs_chunk = chunk.data().NXS();
        CHECK( nxs.size() == nxs_chunk.size() );
        for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {

          CHECK( nxs[i] == nxs_chunk[i] );
        }
      } // THEN

      THEN( "the JXS array is correct" ) {

        decltype(auto) jxs_chunk = chunk.data().JXS();
        CHECK( jxs.size() == jxs_chunk.size() );
        for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {

          CHECK( jxs[i] == jxs_chunk[i] );
        }
      } // THEN

      THEN( "the XSS array is correct" ) {

        decltype(auto) xss_chunk = chunk.data().XSS();
        CHECK( xss.size() == xss_chunk.size() );
        for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "constructing a ContinuousEnergyTable from its components" ) {

      ContinuousEnergyTable base( std::move( table ) );

      std::optional< std::vector< continuous::HPD > > hpd = std::vector< continuous::HPD >{};
      std::optional< std::vector< continuous::MTRH > > mtrh = std::vector< continuous::MTRH >{};
      std::optional< std::vector< continuous::SIGH > > sigh = std::vector< continuous::SIGH >{};
      std::optional< std::vector< continuous::ANDH > > andh = std::vector< continuous::ANDH >{};
      std::optional< std::vector< continuous::DLWH > > dlwh = std::vector< continuous::DLWH >{};
      std::optional< std::vector< continuous::YH > > yh = std::vector< continuous::YH >{};
      for ( unsigned int index = 1; index <= base.NTYPE(); ++index ) {

        hpd->push_back( base.HPD( index ) );
        mtrh->push_back( base.MTRH( index ) );
        sigh->push_back( base.SIGH( index ) );
        andh->push_back( base.ANDH( index ) );
        dlwh->push_back( base.DLWH( index ) );
        yh->push_back( base.YH( index ) );
      }

      ContinuousEnergyTable chunk( 2, 3, 0, base.header(),
                                   base.ESZ(), std::nullopt, std::nullopt,
                                   base.MTR(), base.LQR(),
                                   base.SIG(), base.AND(), base.DLW(),
                                   std::nullopt, std::nullopt,
                                   std::nullopt, std::nullopt, std::nullopt,
                                   std::nullopt, std::nullopt, std::nullopt,
                                   std::nullopt,
                                   base.PTYPE(), std::move( hpd ),
                                   std::move( mtrh ),
                                   std::move( sigh ), std::move( andh ),
                                   std::move( dlwh ), std::move( yh ) );

      THEN( "a ContinuousEnergyTable can be constructed and members can be "
            "tested" ) {

        verifyChunkHe3( chunk );
      }

      THEN( "the IZ array is correct" ) {

        decltype(auto) iz_chunk = chunk.data().IZ();
        CHECK( iz.size() == iz_chunk.size() );
        for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {

          CHECK( iz[i] == iz_chunk[i] );
        }
      } // THEN

      THEN( "the AW array is correct" ) {

        decltype(auto) aw_chunk = chunk.data().AW();
        CHECK( aw.size() == aw_chunk.size() );
        for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {

          CHECK_THAT( aw[i], WithinRel( aw_chunk[i] ) );
        }
      } // THEN

      THEN( "the NXS array is correct" ) {

        decltype(auto) nxs_chunk = chunk.data().NXS();
        CHECK( nxs.size() == nxs_chunk.size() );
        for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {

          CHECK( nxs[i] == nxs_chunk[i] );
        }
      } // THEN

      THEN( "the JXS array is correct" ) {

        decltype(auto) jxs_chunk = chunk.data().JXS();
        CHECK( jxs.size() == jxs_chunk.size() );
        for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {

          CHECK( jxs[i] == jxs_chunk[i] );
        }
      } // THEN

      THEN( "the XSS array is correct" ) {

        decltype(auto) xss_chunk = chunk.data().XSS();
        CHECK( xss.size() == xss_chunk.size() );
        for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ContinuousEnergyTable - NJOY99 U238" ) {

    // the ASCII representation of the XSS array uses no integer values

    auto table = fromFile( "92238.69c" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a ContinuousEnergyTable from a table" ) {

      ContinuousEnergyTable chunk( std::move( table ) );

      THEN( "a ContinuousEnergyTable can be constructed and members can be "
            "tested" ) {

        verifyChunkNJOY99U238( chunk );
      }

      THEN( "the IZ array is correct" ) {

        decltype(auto) iz_chunk = chunk.data().IZ();
        CHECK( iz.size() == iz_chunk.size() );
        for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {

          CHECK( iz[i] == iz_chunk[i] );
        }
      } // THEN

      THEN( "the AW array is correct" ) {

        decltype(auto) aw_chunk = chunk.data().AW();
        CHECK( aw.size() == aw_chunk.size() );
        for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {

          CHECK_THAT( aw[i], WithinRel( aw_chunk[i] ) );
        }
      } // THEN

      THEN( "the NXS array is correct" ) {

        decltype(auto) nxs_chunk = chunk.data().NXS();
        CHECK( nxs.size() == nxs_chunk.size() );
        for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {

          // S, Z, A was added to the NXS array
          switch ( i ) {

            case  8 : { CHECK(      0 == nxs_chunk[i] ); break; }
            case  9 : { CHECK(     92 == nxs_chunk[i] ); break; }
            case 10 : { CHECK(    238 == nxs_chunk[i] ); break; }
            default : { CHECK( nxs[i] == nxs_chunk[i] ); break; }
          }
        }
      } // THEN

      THEN( "the JXS array is correct" ) {

        decltype(auto) jxs_chunk = chunk.data().JXS();
        CHECK( jxs.size() == jxs_chunk.size() );
        for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {

          CHECK( jxs[i] == jxs_chunk[i] );
        }
      } // THEN

      THEN( "the XSS array is correct" ) {

        decltype(auto) xss_chunk = chunk.data().XSS();
        CHECK( xss.size() == xss_chunk.size() );
        for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    // no test to reconstruct this ACE table: older NJOY99 evaluations do not
    // duplicate delayed neutron energy distributions (resulting in two locators
    // that are the same in the DNED block). ACEtk duplicates the data and as
    // such will result in a different XSS array if we reconstruct it from its
    // componenents.

  } // GIVEN
} // SCENARIO

void verifyChunkU235( const ContinuousEnergyTable& chunk ) {

  CHECK( "92235.710nc" == chunk.ZAID() );
  CHECK_THAT( 2.5301e-8, WithinRel( chunk.temperature() ) );

  CHECK( 837481 == chunk.length() );
  CHECK( 92235 == chunk.ZA() );
  CHECK( 76518 == chunk.NES() );
  CHECK( 76518 == chunk.numberEnergyPoints() );
  CHECK( 48 == chunk.NTR() );
  CHECK( 48 == chunk.numberReactions() );
  CHECK( 49 == chunk.totalNumberReactions() );
  CHECK( 45 == chunk.NR() );
  CHECK( 45 == chunk.numberProjectileProductionReactions() );
  CHECK( 33 == chunk.NTRP() );
  CHECK( 33 == chunk.numberPhotonProductionReactions() );
  CHECK( 0 == chunk.NTYPE() );
  CHECK( 0 == chunk.numberSecondaryParticleTypes() );
  CHECK( 6 == chunk.NPCR() );
  CHECK( 6 == chunk.numberDelayedPrecursors() );
  CHECK( 0 == chunk.S() );
  CHECK( 0 == chunk.isomericState() );
  CHECK( 92 == chunk.Z() );
  CHECK( 92 == chunk.atomNumber() );
  CHECK( 235 == chunk.A() );
  CHECK( 235 == chunk.massNumber() );

  // ESZ block
  CHECK( false == chunk.ESZ().empty() );
  CHECK( 76518 == chunk.ESZ().energies().size() );
  CHECK( 76518 == chunk.ESZ().total().size() );
  CHECK( 76518 == chunk.ESZ().disappearance().size() );
  CHECK( 76518 == chunk.ESZ().elastic().size() );
  CHECK( 76518 == chunk.ESZ().heating().size() );

  CHECK_THAT( 1e-11, WithinRel( chunk.ESZ().energies().front() ) );
  CHECK_THAT( 20., WithinRel( chunk.ESZ().energies().back() ) );

  CHECK_THAT( 1e-11, WithinRel( chunk.ESZ().XSS( 1 ) ) );
  CHECK_THAT( 20., WithinRel( chunk.ESZ().XSS( 76518 ) ) );

  // NU block
  CHECK( false == chunk.NU()->empty() );

  CHECK( true == chunk.NU()->hasPromptAndTotalFissionMultiplicity() );

  auto prompt = std::get< njoy::ACEtk::continuous::TabulatedFissionMultiplicity >( chunk.NU()->multiplicity() );
  auto total = std::get< njoy::ACEtk::continuous::TabulatedFissionMultiplicity >( chunk.NU()->totalFissionMultiplicity().value() );

  CHECK( 0 == prompt.NB() );
  CHECK( 79 == prompt.NE() );
  CHECK_THAT( 1e-11, WithinRel( prompt.energies().front() ) );
  CHECK_THAT( 20., WithinRel( prompt.energies().back() ) );
  CHECK_THAT( 2.42085, WithinRel( prompt.multiplicities().front() ) );
  CHECK_THAT( 5.200845, WithinRel( prompt.multiplicities().back() ) );

  CHECK( 0 == total.NB() );
  CHECK( 79 == total.NE() );
  CHECK_THAT( 1e-11, WithinRel( total.energies().front() ) );
  CHECK_THAT( 20., WithinRel( total.energies().back() ) );
  CHECK_THAT( 2.4367, WithinRel( total.multiplicities().front() ) );
  CHECK_THAT( 5.209845, WithinRel( total.multiplicities().back() ) );

  // MTR block
  CHECK( false == chunk.MTR().empty() );
  CHECK( 48 == chunk.MTR().MTs().size() );
  CHECK( 16 == chunk.MTR().MTs().front() );
  CHECK( 4 == chunk.MTR().MTs().back() );
  CHECK( 48 == chunk.MTR().reactionNumbers().size() );
  CHECK( 16 == chunk.MTR().reactionNumbers().front() );
  CHECK( 4 == chunk.MTR().reactionNumbers().back() );

  CHECK( 16 == chunk.MTR().MT( 1 ) );
  CHECK( 4 == chunk.MTR().MT( 48 ) );
  CHECK( 16 == chunk.MTR().reactionNumber( 1 ) );
  CHECK( 4 == chunk.MTR().reactionNumber( 48 ) );

  CHECK( true == chunk.MTR().hasReactionNumber( 16 ) );
  CHECK( true == chunk.MTR().hasReactionNumber( 4 ) );
  CHECK( 1 == chunk.MTR().index( 16 ) );
  CHECK( 48 == chunk.MTR().index( 4 ) );

  // LQR block
  CHECK( false == chunk.LQR().empty() );
  CHECK( 48 == chunk.LQR().QValues().size() );
  CHECK( -5.297781 == chunk.LQR().QValues().front() );
  CHECK( 0. == chunk.LQR().QValues().back() );

  CHECK( -5.297781 == chunk.LQR().QValue( 1 ) );
  CHECK( 0. == chunk.LQR().QValue( 48 ) );

  // TYR block
  CHECK( false == chunk.TYR().empty() );
  CHECK( 48 == chunk.TYR().referenceFrames().size() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.TYR().referenceFrames().front() );
  CHECK( ReferenceFrame::Laboratory == chunk.TYR().referenceFrames().back() );
  CHECK( 48 == chunk.TYR().multiplicities().size() );
  CHECK( 2 == chunk.TYR().multiplicities().front() );
  CHECK( 0 == chunk.TYR().multiplicities().back() );

  CHECK( ReferenceFrame::CentreOfMass == chunk.TYR().referenceFrame( 1 ) );
  CHECK( ReferenceFrame::Laboratory == chunk.TYR().referenceFrame( 48 ) );
  CHECK( 2 == chunk.TYR().multiplicity( 1 ) );
  CHECK( 0 == chunk.TYR().multiplicity( 48 ) );

  // SIG block
  CHECK( false == chunk.SIG().empty() );
  CHECK( 48 == chunk.SIG().NTR() );

  CHECK( 1 == chunk.SIG().LSIG( 1 ) );
  CHECK( 236259 == chunk.SIG().LSIG( 48 ) );

  CHECK( 76460 == chunk.SIG().energyIndex( 1 ) );
  CHECK( 76095 == chunk.SIG().energyIndex( 48 ) );

  CHECK( 59 == chunk.SIG().numberValues( 1 ) );
  CHECK( 424 == chunk.SIG().numberValues( 48 ) );

  auto xs1 = chunk.SIG().crossSectionData( 1 );
  auto xs48 = chunk.SIG().crossSectionData( 48 );
  CHECK( 76460 == xs1.energyIndex() );
  CHECK( 76095 == xs48.energyIndex() );
  CHECK( 59 == xs1.numberValues() );
  CHECK( 424 == xs48.numberValues() );
  CHECK_THAT( 0., WithinRel( xs1.crossSections().front() ) );
  CHECK_THAT( 1.55512000000E-01, WithinRel( xs1.crossSections().back() ) );
  CHECK_THAT( 0., WithinRel( xs48.crossSections().front() ) );
  CHECK_THAT( 3.65016600000E-01, WithinRel( xs48.crossSections().back() ) );

  auto data1 = chunk.SIG().crossSections( 1 );
  auto data48 = chunk.SIG().crossSections( 48 );
  CHECK( 59 == data1.size() );
  CHECK( 424 == data48.size() );
  CHECK_THAT( 0., WithinRel( data1.front() ) );
  CHECK_THAT( 1.55512000000E-01, WithinRel( data1.back() ) );
  CHECK_THAT( 0., WithinRel( data48.front() ) );
  CHECK_THAT( 3.65016600000E-01, WithinRel( data48.back() ) );

  // AND block
  CHECK( false == chunk.AND().empty() );
  CHECK( 45 == chunk.AND().NR() );

  CHECK( 1 == chunk.AND().LAND( 0 ) ); // elastic
  CHECK( 0 == chunk.AND().LAND( 3 ) );
  CHECK( 63802 == chunk.AND().LAND( 44 ) );
  CHECK( -1 == chunk.AND().LAND( 45 ) );

  CHECK( true == std::holds_alternative< AngularDistributionData >( chunk.AND().angularDistributionData( 0 ) ) ); // elastic
  CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( chunk.AND().angularDistributionData( 3 ) ) );
  CHECK( true == std::holds_alternative< AngularDistributionData >( chunk.AND().angularDistributionData( 44 ) ) );
  CHECK( true == std::holds_alternative< DistributionGivenElsewhere >( chunk.AND().angularDistributionData( 45 ) ) );

  // DLW block
  CHECK( false == chunk.DLW().empty() );
  CHECK( 45 == chunk.DLW().NR() );

  CHECK( 1 == chunk.DLW().LDLW( 1 ) );
  CHECK( 48133 == chunk.DLW().LDLW( 44 ) );
  CHECK( 48144 == chunk.DLW().LDLW( 45 ) );

  CHECK( true == std::holds_alternative< KalbachMannDistributionData >( chunk.DLW().energyDistributionData( 1 ) ) );
  CHECK( true == std::holds_alternative< LevelScatteringDistribution >( chunk.DLW().energyDistributionData( 44 ) ) );
  CHECK( true == std::holds_alternative< KalbachMannDistributionData >( chunk.DLW().energyDistributionData( 45 ) ) );

  // GPD block
  CHECK( false == chunk.GPD()->empty() );
  CHECK( 76518 == chunk.GPD()->totalProduction().size() );

  CHECK_THAT( 2.433297E+05, WithinRel( chunk.GPD()->totalProduction().front() ) );
  CHECK_THAT( 31.07, WithinRel( chunk.GPD()->totalProduction().back() ) );

  // MTRP block
  CHECK( false == chunk.MTRP()->empty() );
  CHECK( 33 == chunk.MTRP()->MTs().size() );
  CHECK( 4001 == chunk.MTRP()->MTs().front() );
  CHECK( 3001 == chunk.MTRP()->MTs().back() );
  CHECK( 33 == chunk.MTRP()->reactionNumbers().size() );
  CHECK( 4001 == chunk.MTRP()->reactionNumbers().front() );
  CHECK( 3001 == chunk.MTRP()->reactionNumbers().back() );

  CHECK( 4001 == chunk.MTRP()->MT( 1 ) );
  CHECK( 3001 == chunk.MTRP()->MT( 33 ) );
  CHECK( 4001 == chunk.MTRP()->reactionNumber( 1 ) );
  CHECK( 3001 == chunk.MTRP()->reactionNumber( 33 ) );

  CHECK( true == chunk.MTRP()->hasReactionNumber( 4001 ) );
  CHECK( true == chunk.MTRP()->hasReactionNumber( 3001 ) );
  CHECK( 1 == chunk.MTRP()->index( 4001 ) );
  CHECK( 33 == chunk.MTRP()->index( 3001 ) );

  // SIGP block
  CHECK( false == chunk.SIGP()->empty() );
  CHECK( 33 == chunk.SIGP()->NTRP() );

  CHECK( 1 == chunk.SIGP()->LSIG( 1 ) );
  CHECK( 37 == chunk.SIGP()->LSIG( 3 ) );
  CHECK( 1155 == chunk.SIGP()->LSIG( 33 ) );

  CHECK( true == std::holds_alternative< TabulatedSecondaryParticleMultiplicity >( chunk.SIGP()->crossSectionData( 1 ) ) );
  CHECK( true == std::holds_alternative< TabulatedSecondaryParticleMultiplicity >( chunk.SIGP()->crossSectionData( 3 ) ) );
  CHECK( true == std::holds_alternative< PhotonProductionCrossSectionData >( chunk.SIGP()->crossSectionData( 33 ) ) );

  // ANDP block
  CHECK( false == chunk.ANDP()->empty() );
  CHECK( 33 == chunk.ANDP()->NR() );

  CHECK( 0 == chunk.ANDP()->LAND( 1 ) );
  CHECK( 0 == chunk.ANDP()->LAND( 3 ) );
  CHECK( 0 == chunk.ANDP()->LAND( 33 ) );

  CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( chunk.ANDP()->angularDistributionData( 1 ) ) );
  CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( chunk.ANDP()->angularDistributionData( 3 ) ) );
  CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( chunk.ANDP()->angularDistributionData( 33 ) ) );

  // DLWP block
  CHECK( false == chunk.DLWP()->empty() );
  CHECK( 33 == chunk.DLWP()->NR() );

  CHECK( 1 == chunk.DLWP()->LDLW( 1 ) );
  CHECK( 23 == chunk.DLWP()->LDLW( 3 ) );
  CHECK( 1139 == chunk.DLWP()->LDLW( 33 ) );

  CHECK( true == std::holds_alternative< DiscretePhotonDistribution >( chunk.DLWP()->energyDistributionData( 1 ) ) );
  CHECK( true == std::holds_alternative< DiscretePhotonDistribution >( chunk.DLWP()->energyDistributionData( 3 ) ) );
  CHECK( true == std::holds_alternative< OutgoingEnergyDistributionData >( chunk.DLWP()->energyDistributionData( 33 ) ) );

  // YP block
  CHECK( false == chunk.YP()->empty() );
  CHECK( 3 == chunk.YP()->MTs().size() );
  CHECK( 4 == chunk.YP()->MTs().front() );
  CHECK( 102 == chunk.YP()->MTs().back() );
  CHECK( 3 == chunk.YP()->reactionNumbers().size() );
  CHECK( 4 == chunk.YP()->reactionNumbers().front() );
  CHECK( 102 == chunk.YP()->reactionNumbers().back() );

  CHECK( 4 == chunk.YP()->MT( 1 ) );
  CHECK( 102 == chunk.YP()->MT( 3 ) );
  CHECK( 4 == chunk.YP()->reactionNumber( 1 ) );
  CHECK( 102 == chunk.YP()->reactionNumber( 3 ) );

  CHECK( true == chunk.YP()->hasReactionNumber( 4 ) );
  CHECK( true == chunk.YP()->hasReactionNumber( 18 ) );
  CHECK( true == chunk.YP()->hasReactionNumber( 102 ) );
  CHECK( 1 == chunk.YP()->index( 4 ) );
  CHECK( 2 == chunk.YP()->index( 18 ) );
  CHECK( 3 == chunk.YP()->index( 102 ) );

  // UNR block
  CHECK( false == chunk.UNR()->empty() );

  CHECK( 19 == chunk.UNR()->numberIncidentEnergies() );

  auto unr1 = chunk.UNR()->probabilityTable( 1 );
  auto unr19 = chunk.UNR()->probabilityTable( 19 );
  CHECK_THAT( 2.25000100000E-03, WithinRel( unr1.incidentEnergy() ) );
  CHECK_THAT( 2.49999900000E-02, WithinRel( unr19.incidentEnergy() ) );
  CHECK( 16 == unr1.numberBins() );
  CHECK( 16 == unr19.numberBins() );
  CHECK_THAT( 1., WithinRel( unr1.heating().front() ) );
  CHECK_THAT( 1., WithinRel( unr1.heating().back() ) );
  CHECK_THAT( 1., WithinRel( unr19.heating().front() ) );
  CHECK_THAT( 1., WithinRel( unr19.heating().back() ) );

  // DNU block
  CHECK( false == chunk.DNU()->empty() );

  CHECK( false == chunk.DNU()->hasPromptAndTotalFissionMultiplicity() );

  auto delayed = std::get< njoy::ACEtk::continuous::TabulatedFissionMultiplicity >( chunk.DNU()->multiplicity() );

  CHECK( 0 == delayed.NB() );
  CHECK( 6 == delayed.NE() );
  CHECK_THAT( 1e-11, WithinRel( delayed.energies().front() ) );
  CHECK_THAT( 20., WithinRel( delayed.energies().back() ) );
  CHECK_THAT( 0.01585, WithinRel( delayed.multiplicities().front() ) );
  CHECK_THAT( 0.009, WithinRel( delayed.multiplicities().back() ) );

  // BDD block
  CHECK( false == chunk.BDD()->empty() );

  CHECK( 6 == chunk.BDD()->NPCR() );
  CHECK( 6 == chunk.BDD()->numberDelayedPrecursors() );

  CHECK_THAT( 1.33360E-10, WithinRel( chunk.BDD()->precursorGroupData( 1 ).DEC() ) );
  CHECK_THAT( 2.85300E-08, WithinRel( chunk.BDD()->precursorGroupData( 6 ).DEC() ) );

  // DNED block
  CHECK( false == chunk.DNED()->empty() );

  CHECK( 1 == chunk.DNED()->LDLW( 1 ) );
  CHECK( 7944 == chunk.DNED()->LDLW( 6 ) );

  CHECK( true == std::holds_alternative< OutgoingEnergyDistributionData >( chunk.DNED()->energyDistributionData( 1 ) ) );
  CHECK( true == std::holds_alternative< OutgoingEnergyDistributionData >( chunk.DNED()->energyDistributionData( 6 ) ) );

  CHECK( false == chunk.DNED()->referenceFrame( 1 ).has_value() );
  CHECK( false == chunk.DNED()->referenceFrame( 6 ).has_value() );

  // PTYPE block
  CHECK( false == chunk.PTYPE().has_value() );

  // NTRO block
  CHECK( false == chunk.NTRO().has_value() );

  // IXS block
  CHECK( false == chunk.IXS().has_value() );
}

void verifyChunkHe3( const ContinuousEnergyTable& chunk ) {

  CHECK( "2003.710nc" == chunk.ZAID() );
  CHECK_THAT( 2.5301e-8, WithinRel( chunk.temperature() ) );

  CHECK( 10004 == chunk.length() );
  CHECK( 2003 == chunk.ZA() );
  CHECK( 693 == chunk.NES() );
  CHECK( 693 == chunk.numberEnergyPoints() );
  CHECK( 8 == chunk.NTR() );
  CHECK( 8 == chunk.numberReactions() );
  CHECK( 9 == chunk.totalNumberReactions() );
  CHECK( 0 == chunk.NR() );
  CHECK( 0 == chunk.numberProjectileProductionReactions() );
  CHECK( 0 == chunk.NTRP() );
  CHECK( 0 == chunk.numberPhotonProductionReactions() );
  CHECK( 1 == chunk.NTYPE() );
  CHECK( 1 == chunk.numberSecondaryParticleTypes() );
  CHECK( 0 == chunk.NPCR() );
  CHECK( 0 == chunk.numberDelayedPrecursors() );
  CHECK( 0 == chunk.S() );
  CHECK( 0 == chunk.isomericState() );
  CHECK( 2 == chunk.Z() );
  CHECK( 2 == chunk.atomNumber() );
  CHECK( 3 == chunk.A() );
  CHECK( 3 == chunk.massNumber() );

  // ESZ block
  CHECK( false == chunk.ESZ().empty() );
  CHECK( 693 == chunk.ESZ().energies().size() );
  CHECK( 693 == chunk.ESZ().total().size() );
  CHECK( 693 == chunk.ESZ().disappearance().size() );
  CHECK( 693 == chunk.ESZ().elastic().size() );
  CHECK( 693 == chunk.ESZ().heating().size() );

  CHECK_THAT( 1e-11, WithinRel( chunk.ESZ().energies().front() ) );
  CHECK_THAT( 20., WithinRel( chunk.ESZ().energies().back() ) );

  CHECK_THAT( 1e-11, WithinRel( chunk.ESZ().XSS( 1 ) ) );
  CHECK_THAT( 20., WithinRel( chunk.ESZ().XSS( 693 ) ) );

  // NU block
  CHECK( false == chunk.NU().has_value() );

  // LQR block
  CHECK( false == chunk.LQR().empty() );
  CHECK( 8 == chunk.LQR().QValues().size() );
  CHECK( 20.57778 == chunk.LQR().QValues().front() );
  CHECK( 0. == chunk.LQR().QValues().back() );

  CHECK( 20.57778 == chunk.LQR().QValue( 1 ) );
  CHECK( 0. == chunk.LQR().QValue( 8 ) );

  // TYR block
  CHECK( false == chunk.TYR().empty() );
  CHECK( 8 == chunk.TYR().referenceFrames().size() );
  CHECK( ReferenceFrame::Laboratory == chunk.TYR().referenceFrames().front() );
  CHECK( ReferenceFrame::Laboratory == chunk.TYR().referenceFrames().back() );
  CHECK( 8 == chunk.TYR().multiplicities().size() );
  CHECK( 0 == chunk.TYR().multiplicities().front() );
  CHECK( 0 == chunk.TYR().multiplicities().back() );

  CHECK( ReferenceFrame::Laboratory == chunk.TYR().referenceFrame( 1 ) );
  CHECK( ReferenceFrame::Laboratory == chunk.TYR().referenceFrame( 8 ) );
  CHECK( 0 == chunk.TYR().multiplicity( 1 ) );
  CHECK( 0 == chunk.TYR().multiplicity( 8 ) );

  // SIG block
  CHECK( false == chunk.SIG().empty() );
  CHECK( 8 == chunk.SIG().NTR() );

  CHECK( 1 == chunk.SIG().LSIG( 1 ) );
  CHECK( 3668 == chunk.SIG().LSIG( 8 ) );

  CHECK( 1 == chunk.SIG().energyIndex( 1 ) );
  CHECK( 1 == chunk.SIG().energyIndex( 8 ) );

  CHECK( 693 == chunk.SIG().numberValues( 1 ) );
  CHECK( 693 == chunk.SIG().numberValues( 8 ) );

  auto xs1 = chunk.SIG().crossSectionData( 1 );
  auto xs8 = chunk.SIG().crossSectionData( 8 );
  CHECK( 1 == xs1.energyIndex() );
  CHECK( 1 == xs8.energyIndex() );
  CHECK( 693 == xs1.numberValues() );
  CHECK( 693 == xs8.numberValues() );
  CHECK_THAT( 2.76519500000E-03, WithinRel( xs1.crossSections().front() ) );
  CHECK_THAT( 2.86200000000E-05, WithinRel( xs1.crossSections().back() ) );
  CHECK_THAT( 5.36998100000E+02, WithinRel( xs8.crossSections().front() ) );
  CHECK_THAT( 2.63996800000E-03, WithinRel( xs8.crossSections().back() ) );

  auto data1 = chunk.SIG().crossSections( 1 );
  auto data8 = chunk.SIG().crossSections( 8 );
  CHECK( 693 == data1.size() );
  CHECK( 693 == data8.size() );
  CHECK_THAT( 2.76519500000E-03, WithinRel( data1.front() ) );
  CHECK_THAT( 2.86200000000E-05, WithinRel( data1.back() ) );
  CHECK_THAT( 5.36998100000E+02, WithinRel( data8.front() ) );
  CHECK_THAT( 2.63996800000E-03, WithinRel( data8.back() ) );

  // AND block
  CHECK( false == chunk.AND().empty() );
  CHECK( 0 == chunk.AND().NR() );

  CHECK( 1 == chunk.AND().LAND( 0 ) ); // elastic

  CHECK( true == std::holds_alternative< AngularDistributionData >( chunk.AND().angularDistributionData( 0 ) ) ); // elastic

  // DLW block
  CHECK( true == chunk.DLW().empty() );
  CHECK( 0 == chunk.DLW().NR() );

  // GPD block
  CHECK( false == chunk.GPD().has_value() );

  // MTRP block
  CHECK( false == chunk.MTRP().has_value() );

  // SIGP block
  CHECK( false == chunk.SIGP().has_value() );

  // ANDP block
  CHECK( false == chunk.ANDP().has_value() );

  // DLWP block
  CHECK( false == chunk.DLWP().has_value() );

  // YP block
  CHECK( false == chunk.YP().has_value() );

  // UNR block
  CHECK( false == chunk.UNR().has_value() );

  // DNU block
  CHECK( false == chunk.DNU().has_value() );

  // BDD block
  CHECK( false == chunk.BDD().has_value() );

  // DNED block
  CHECK( false == chunk.DNED().has_value() );

  // PTYPE block
  CHECK( false == chunk.PTYPE()->empty() );
  CHECK( 1 == chunk.PTYPE()->NTYPE() );
  CHECK( 1 == chunk.PTYPE()->IPs().size() );

  CHECK( 34 == chunk.PTYPE()->IP( 1 ) );
  CHECK( 34 == chunk.PTYPE()->IPs().front() );

  // NTRO block
  CHECK( false == chunk.NTRO()->empty() );
  CHECK( 1 == chunk.NTRO()->NTYPE() );
  CHECK( 1 == chunk.NTRO()->NPs().size() );

  CHECK( 1 == chunk.NTRO()->NP( 1 ) );
  CHECK( 1 == chunk.NTRO()->NPs().front() );

  // IXS block
  CHECK( false == chunk.IXS()->empty() );
  CHECK( 1 == chunk.IXS()->NTYPE() );

  CHECK(  8564 == chunk.IXS()->HPD( 1 ) );
  CHECK(  9952 == chunk.IXS()->MTRH( 1 ) );
  CHECK(  9953 == chunk.IXS()->TYRH( 1 ) );
  CHECK(  9954 == chunk.IXS()->LSIGH( 1 ) );
  CHECK(  9955 == chunk.IXS()->SIGH( 1 ) );
  CHECK(  9963 == chunk.IXS()->LANDH( 1 ) );
  CHECK(  9964 == chunk.IXS()->ANDH( 1 ) );
  CHECK(  9991 == chunk.IXS()->LDLWH( 1 ) );
  CHECK(  9992 == chunk.IXS()->DLWH( 1 ) );
  CHECK( 10003 == chunk.IXS()->YP( 1 ) );

  // HPD(1) block
  CHECK( false == chunk.HPD(1).empty() );

  CHECK( 1 == chunk.HPD(1).energyIndex() );
  CHECK( 693 == chunk.HPD(1).numberValues() );
  CHECK_THAT( 2.76519500000E-03, WithinRel( chunk.HPD(1).totalProduction().front() ) );
  CHECK_THAT( 2.86200000000E-05, WithinRel( chunk.HPD(1).totalProduction().back() ) );
  CHECK_THAT( 0., WithinRel( chunk.HPD(1).heating().front() ) );
  CHECK_THAT( 1.68611800000E-04, WithinRel( chunk.HPD(1).heating().back() ) );

  // MTRH(1) block
  CHECK( false == chunk.MTRH(1).empty() );
  CHECK( 1 == chunk.MTRH(1).MTs().size() );
  CHECK( 102 == chunk.MTRH(1).MTs().front() );
  CHECK( 1 == chunk.MTRH(1).reactionNumbers().size() );
  CHECK( 102 == chunk.MTRH(1).reactionNumbers().front() );

  CHECK( 102 == chunk.MTRH(1).MT( 1 ) );
  CHECK( 102 == chunk.MTRH(1).reactionNumber( 1 ) );

  CHECK( true == chunk.MTRH(1).hasReactionNumber( 102 ) );
  CHECK( 1 == chunk.MTRH(1).index( 102 ) );

  // TYRH(1) block
  CHECK( false == chunk.TYRH(1).empty() );
  CHECK( 1 == chunk.TYRH(1).referenceFrames().size() );
  CHECK( ReferenceFrame::Laboratory == chunk.TYRH(1).referenceFrames().front() );
  CHECK( ReferenceFrame::Laboratory == chunk.TYRH(1).referenceFrame( 1 ) );

  // SIGH(1) block
  CHECK( false == chunk.SIGH(1).empty() );

  auto multiplicity = chunk.SIGH(1).crossSectionData( 1 );
  CHECK( 12 == multiplicity.MFTYPE() );
  CHECK( 12 == multiplicity.type() );
  CHECK( 102 == multiplicity.MT() );
  CHECK( 102 == multiplicity.reactionNumber() );

  CHECK( 0 == multiplicity.interpolationData().NB() );
  CHECK( 0 == multiplicity.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == multiplicity.interpolationData().INT().size() );
  CHECK( 0 == multiplicity.interpolationData().interpolants().size() );
  CHECK( 0 == multiplicity.interpolationData().NBT().size() );
  CHECK( 0 == multiplicity.interpolationData().boundaries().size() );

  CHECK( 0 == multiplicity.NB() );
  CHECK( 0 == multiplicity.numberInterpolationRegions() );
  CHECK( 0 == multiplicity.INT().size() );
  CHECK( 0 == multiplicity.interpolants().size() );
  CHECK( 0 == multiplicity.NBT().size() );
  CHECK( 0 == multiplicity.boundaries().size() );

  CHECK( 2 == multiplicity.NE() );
  CHECK( 2 == multiplicity.numberValues() );

  CHECK( 2 == multiplicity.energies().size() );
  CHECK_THAT( 1e-11, WithinRel( multiplicity.energies().front() ) );
  CHECK_THAT( 20., WithinRel( multiplicity.energies().back() ) );

  CHECK( 2 == multiplicity.multiplicities().size() );
  CHECK_THAT( 1., WithinRel( multiplicity.multiplicities().front() ) );
  CHECK_THAT( 1., WithinRel( multiplicity.multiplicities().back() ) );

  // ANDH(1) block
  CHECK( false == chunk.ANDH(1).empty() );
  CHECK( 1 == chunk.ANDH(1).NR() );

  CHECK( 1 == chunk.ANDH(1).LAND( 1 ) );

  CHECK( true == std::holds_alternative< AngularDistributionData >( chunk.ANDH(1).angularDistributionData( 1 ) ) );

  // DLWH(1) block
  CHECK( false == chunk.DLWH(1).empty() );
  CHECK( 1 == chunk.DLWH(1).NR() );

  CHECK( 1 == chunk.DLWH(1).LDLW( 1 ) );

  CHECK( true == std::holds_alternative< TwoBodyTransferDistribution >( chunk.DLWH(1).energyDistributionData( 1 ) ) );

  CHECK( ReferenceFrame::Laboratory == chunk.DLWH(1).referenceFrame( 1 ).value() );

  // YH(1) block
  CHECK( false == chunk.YH(1).empty() );
  CHECK( 1 == chunk.YH(1).MTs().size() );
  CHECK( 102 == chunk.YH(1).MTs().front() );
  CHECK( 1 == chunk.YH(1).reactionNumbers().size() );
  CHECK( 102 == chunk.YH(1).reactionNumbers().front() );

  CHECK( 102 == chunk.YH(1).MT( 1 ) );
}

void verifyChunkNJOY99U238( const ContinuousEnergyTable& chunk ) {

  CHECK( "92238.69c" == chunk.ZAID() );
  CHECK_THAT( 2.5301e-8, WithinRel( chunk.temperature() ) );

  CHECK( 874492 == chunk.length() );
  CHECK( 92238 == chunk.ZA() );
  CHECK( 78709 == chunk.NES() );
  CHECK( 78709 == chunk.numberEnergyPoints() );
  CHECK( 47 == chunk.NTR() );
  CHECK( 47 == chunk.numberReactions() );
  CHECK( 48 == chunk.totalNumberReactions() );
  CHECK( 45 == chunk.NR() );
  CHECK( 45 == chunk.numberProjectileProductionReactions() );
  CHECK( 6 == chunk.NTRP() );
  CHECK( 6 == chunk.numberPhotonProductionReactions() );
  CHECK( 0 == chunk.NTYPE() );
  CHECK( 0 == chunk.numberSecondaryParticleTypes() );
  CHECK( 6 == chunk.NPCR() );
  CHECK( 6 == chunk.numberDelayedPrecursors() );
  CHECK( 0 == chunk.S() );
  CHECK( 0 == chunk.isomericState() );
  CHECK( 92 == chunk.Z() );
  CHECK( 92 == chunk.atomNumber() );
  CHECK( 238 == chunk.A() );
  CHECK( 238 == chunk.massNumber() );

  // ESZ block
  CHECK( false == chunk.ESZ().empty() );
  CHECK( 78709 == chunk.ESZ().energies().size() );
  CHECK( 78709 == chunk.ESZ().total().size() );
  CHECK( 78709 == chunk.ESZ().disappearance().size() );
  CHECK( 78709 == chunk.ESZ().elastic().size() );
  CHECK( 78709 == chunk.ESZ().heating().size() );

  CHECK_THAT( 1e-11, WithinRel( chunk.ESZ().energies().front() ) );
  CHECK_THAT( 30., WithinRel( chunk.ESZ().energies().back() ) );

  CHECK_THAT( 1e-11, WithinRel( chunk.ESZ().XSS( 1 ) ) );
  CHECK_THAT( 30., WithinRel( chunk.ESZ().XSS( 78709 ) ) );

  // NU block
  CHECK( false == chunk.NU()->empty() );

  CHECK( true == chunk.NU()->hasPromptAndTotalFissionMultiplicity() );

  auto prompt = std::get< njoy::ACEtk::continuous::TabulatedFissionMultiplicity >( chunk.NU()->multiplicity() );
  auto total = std::get< njoy::ACEtk::continuous::TabulatedFissionMultiplicity >( chunk.NU()->totalFissionMultiplicity().value() );

  CHECK( 0 == prompt.NB() );
  CHECK( 6 == prompt.NE() );
  CHECK_THAT( 1e-11, WithinRel( prompt.energies().front() ) );
  CHECK_THAT( 30., WithinRel( prompt.energies().back() ) );
  CHECK_THAT( 2.448088, WithinRel( prompt.multiplicities().front() ) );
  CHECK_THAT( 6.4, WithinRel( prompt.multiplicities().back() ) );

  CHECK( 0 == total.NB() );
  CHECK( 8 == total.NE() );
  CHECK_THAT( 1e-11, WithinRel( total.energies().front() ) );
  CHECK_THAT( 30., WithinRel( total.energies().back() ) );
  CHECK_THAT( 2.492088, WithinRel( total.multiplicities().front() ) );
  CHECK_THAT( 6.426, WithinRel( total.multiplicities().back() ) );

  // MTR block
  CHECK( false == chunk.MTR().empty() );
  CHECK( 47 == chunk.MTR().MTs().size() );
  CHECK( 16 == chunk.MTR().MTs().front() );
  CHECK( 444 == chunk.MTR().MTs().back() );
  CHECK( 47 == chunk.MTR().reactionNumbers().size() );
  CHECK( 16 == chunk.MTR().reactionNumbers().front() );
  CHECK( 444 == chunk.MTR().reactionNumbers().back() );

  CHECK( 16 == chunk.MTR().MT( 1 ) );
  CHECK( 444 == chunk.MTR().MT( 47 ) );
  CHECK( 16 == chunk.MTR().reactionNumber( 1 ) );
  CHECK( 444 == chunk.MTR().reactionNumber( 47 ) );

  CHECK( true == chunk.MTR().hasReactionNumber( 16 ) );
  CHECK( true == chunk.MTR().hasReactionNumber( 444 ) );
  CHECK( 1 == chunk.MTR().index( 16 ) );
  CHECK( 47 == chunk.MTR().index( 444 ) );

  // LQR block
  CHECK( false == chunk.LQR().empty() );
  CHECK( 47 == chunk.LQR().QValues().size() );
  CHECK( -6.1528 == chunk.LQR().QValues().front() );
  CHECK( 0. == chunk.LQR().QValues().back() );

  CHECK( -6.1528 == chunk.LQR().QValue( 1 ) );
  CHECK( 0. == chunk.LQR().QValue( 47 ) );

  // TYR block
  CHECK( false == chunk.TYR().empty() );
  CHECK( 47 == chunk.TYR().referenceFrames().size() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.TYR().referenceFrames().front() );
  CHECK( ReferenceFrame::Laboratory == chunk.TYR().referenceFrames().back() );
  CHECK( 47 == chunk.TYR().multiplicities().size() );
  CHECK( 2 == chunk.TYR().multiplicities().front() );
  CHECK( 0 == chunk.TYR().multiplicities().back() );

  CHECK( ReferenceFrame::CentreOfMass == chunk.TYR().referenceFrame( 1 ) );
  CHECK( ReferenceFrame::Laboratory == chunk.TYR().referenceFrame( 47 ) );
  CHECK( 2 == chunk.TYR().multiplicity( 1 ) );
  CHECK( 0 == chunk.TYR().multiplicity( 47 ) );

  // SIG block
  CHECK( false == chunk.SIG().empty() );
  CHECK( 47 == chunk.SIG().NTR() );

  CHECK( 1 == chunk.SIG().LSIG( 1 ) );
  CHECK( 165936 == chunk.SIG().LSIG( 47 ) );

  CHECK( 78604 == chunk.SIG().energyIndex( 1 ) );
  CHECK( 1 == chunk.SIG().energyIndex( 47 ) );

  CHECK( 106 == chunk.SIG().numberValues( 1 ) );
  CHECK( 78709 == chunk.SIG().numberValues( 47 ) );

  auto xs1 = chunk.SIG().crossSectionData( 1 );
  auto xs47 = chunk.SIG().crossSectionData( 47 );
  CHECK( 78604 == xs1.energyIndex() );
  CHECK( 1 == xs47.energyIndex() );
  CHECK( 106 == xs1.numberValues() );
  CHECK( 78709 == xs47.numberValues() );
  CHECK_THAT( 0., WithinRel( xs1.crossSections().front() ) );
  CHECK_THAT( 1.387829e-1, WithinRel( xs1.crossSections().back() ) );
  CHECK_THAT( 6.560634e-4, WithinRel( xs47.crossSections().front() ) );
  CHECK_THAT( 3.159912e-1, WithinRel( xs47.crossSections().back() ) );

  auto data1 = chunk.SIG().crossSections( 1 );
  auto data47 = chunk.SIG().crossSections( 47 );
  CHECK( 106 == data1.size() );
  CHECK( 78709 == data47.size() );
  CHECK_THAT( 0., WithinRel( data1.front() ) );
  CHECK_THAT( 1.387829e-1, WithinRel( data1.back() ) );
  CHECK_THAT( 6.560634e-4, WithinRel( data47.front() ) );
  CHECK_THAT( 3.159912e-1, WithinRel( data47.back() ) );

  // AND block
  CHECK( false == chunk.AND().empty() );
  CHECK( 45 == chunk.AND().NR() );

  CHECK( 1 == chunk.AND().LAND( 0 ) ); // elastic
  CHECK( -1 == chunk.AND().LAND( 2 ) );
  CHECK( 0 == chunk.AND().LAND( 3 ) );
  CHECK( 44014 == chunk.AND().LAND( 44 ) );
  CHECK( -1 == chunk.AND().LAND( 45 ) );

  CHECK( true == std::holds_alternative< AngularDistributionData >( chunk.AND().angularDistributionData( 0 ) ) ); // elastic
  CHECK( true == std::holds_alternative< DistributionGivenElsewhere >( chunk.AND().angularDistributionData( 2 ) ) );
  CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( chunk.AND().angularDistributionData( 3 ) ) );
  CHECK( true == std::holds_alternative< AngularDistributionData >( chunk.AND().angularDistributionData( 44 ) ) );
  CHECK( true == std::holds_alternative< DistributionGivenElsewhere >( chunk.AND().angularDistributionData( 45 ) ) );

  // DLW block
  CHECK( false == chunk.DLW().empty() );
  CHECK( 45 == chunk.DLW().NR() );

  CHECK( 1 == chunk.DLW().LDLW( 1 ) );
  CHECK( 71788 == chunk.DLW().LDLW( 44 ) );
  CHECK( 71799 == chunk.DLW().LDLW( 45 ) );

  CHECK( true == std::holds_alternative< KalbachMannDistributionData >( chunk.DLW().energyDistributionData( 1 ) ) );
  CHECK( true == std::holds_alternative< LevelScatteringDistribution >( chunk.DLW().energyDistributionData( 44 ) ) );
  CHECK( true == std::holds_alternative< KalbachMannDistributionData >( chunk.DLW().energyDistributionData( 45 ) ) );

  // GPD block
  CHECK( false == chunk.GPD()->empty() );
  CHECK( 78709 == chunk.GPD()->totalProduction().size() );

  CHECK_THAT( 589.4728, WithinRel( chunk.GPD()->totalProduction().front() ) );
  CHECK_THAT( 17.12507, WithinRel( chunk.GPD()->totalProduction().back() ) );

  // MTRP block
  CHECK( false == chunk.MTRP()->empty() );
  CHECK( 6 == chunk.MTRP()->MTs().size() );
  CHECK( 18001 == chunk.MTRP()->MTs().front() );
  CHECK( 3004 == chunk.MTRP()->MTs().back() );
  CHECK( 6 == chunk.MTRP()->reactionNumbers().size() );
  CHECK( 18001 == chunk.MTRP()->reactionNumbers().front() );
  CHECK( 3004 == chunk.MTRP()->reactionNumbers().back() );

  CHECK( 18001 == chunk.MTRP()->MT( 1 ) );
  CHECK( 3004 == chunk.MTRP()->MT( 6 ) );
  CHECK( 18001 == chunk.MTRP()->reactionNumber( 1 ) );
  CHECK( 3004 == chunk.MTRP()->reactionNumber( 6 ) );

  CHECK( true == chunk.MTRP()->hasReactionNumber( 18001 ) );
  CHECK( true == chunk.MTRP()->hasReactionNumber( 3004 ) );
  CHECK( 1 == chunk.MTRP()->index( 18001 ) );
  CHECK( 6 == chunk.MTRP()->index( 3004 ) );

  // SIGP block
  CHECK( false == chunk.SIGP()->empty() );
  CHECK( 6 == chunk.SIGP()->NTRP() );

  CHECK( 1 == chunk.SIGP()->LSIG( 1 ) );
  CHECK( 19 == chunk.SIGP()->LSIG( 3 ) );
  CHECK( 273 == chunk.SIGP()->LSIG( 6 ) );

  CHECK( true == std::holds_alternative< TabulatedSecondaryParticleMultiplicity >( chunk.SIGP()->crossSectionData( 1 ) ) );
  CHECK( true == std::holds_alternative< PhotonProductionCrossSectionData >( chunk.SIGP()->crossSectionData( 3 ) ) );
  CHECK( true == std::holds_alternative< PhotonProductionCrossSectionData >( chunk.SIGP()->crossSectionData( 6 ) ) );

  // ANDP block
  CHECK( false == chunk.ANDP()->empty() );
  CHECK( 6 == chunk.ANDP()->NR() );

  CHECK( 0 == chunk.ANDP()->LAND( 1 ) );
  CHECK( 0 == chunk.ANDP()->LAND( 3 ) );
  CHECK( 0 == chunk.ANDP()->LAND( 6 ) );

  CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( chunk.ANDP()->angularDistributionData( 1 ) ) );
  CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( chunk.ANDP()->angularDistributionData( 3 ) ) );
  CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( chunk.ANDP()->angularDistributionData( 6 ) ) );

  // DLWP block
  CHECK( false == chunk.DLWP()->empty() );
  CHECK( 6 == chunk.DLWP()->NR() );

  CHECK( 1 == chunk.DLWP()->LDLW( 1 ) );
  CHECK( 759 == chunk.DLWP()->LDLW( 3 ) );
  CHECK( 792 == chunk.DLWP()->LDLW( 6 ) );

  CHECK( true == std::holds_alternative< OutgoingEnergyDistributionData >( chunk.DLWP()->energyDistributionData( 1 ) ) );
  CHECK( true == std::holds_alternative< DiscretePhotonDistribution >( chunk.DLWP()->energyDistributionData( 3 ) ) );
  CHECK( true == std::holds_alternative< OutgoingEnergyDistributionData >( chunk.DLWP()->energyDistributionData( 6 ) ) );

  // YP block
  CHECK( false == chunk.YP()->empty() );
  CHECK( 2 == chunk.YP()->MTs().size() );
  CHECK( 18 == chunk.YP()->MTs().front() );
  CHECK( 102 == chunk.YP()->MTs().back() );
  CHECK( 2 == chunk.YP()->reactionNumbers().size() );
  CHECK( 18 == chunk.YP()->reactionNumbers().front() );
  CHECK( 102 == chunk.YP()->reactionNumbers().back() );

  CHECK( 18 == chunk.YP()->MT( 1 ) );
  CHECK( 102 == chunk.YP()->MT( 2 ) );
  CHECK( 18 == chunk.YP()->reactionNumber( 1 ) );
  CHECK( 102 == chunk.YP()->reactionNumber( 2 ) );

  CHECK( true == chunk.YP()->hasReactionNumber( 18 ) );
  CHECK( true == chunk.YP()->hasReactionNumber( 102 ) );
  CHECK( 1 == chunk.YP()->index( 18 ) );
  CHECK( 2 == chunk.YP()->index( 102 ) );

  // UNR block
  CHECK( false == chunk.UNR()->empty() );

  CHECK( 23 == chunk.UNR()->numberIncidentEnergies() );

  auto unr1 = chunk.UNR()->probabilityTable( 1 );
  auto unr23 = chunk.UNR()->probabilityTable( 23 );
  CHECK_THAT( 1.000001E-02, WithinRel( unr1.incidentEnergy() ) );
  CHECK_THAT( 1.490287E-01, WithinRel( unr23.incidentEnergy() ) );
  CHECK( 20 == unr1.numberBins() );
  CHECK( 20 == unr23.numberBins() );
  CHECK_THAT( 1.12201615476, WithinRel( unr1.heating().front() ) );
  CHECK_THAT( .981419270377, WithinRel( unr1.heating().back() ) );
  CHECK_THAT( .958067726215, WithinRel( unr23.heating().front() ) );
  CHECK_THAT( 1.02349211485, WithinRel( unr23.heating().back() ) );

  // DNU block
  CHECK( false == chunk.DNU()->empty() );

  CHECK( false == chunk.DNU()->hasPromptAndTotalFissionMultiplicity() );

  auto delayed = std::get< njoy::ACEtk::continuous::TabulatedFissionMultiplicity >( chunk.DNU()->multiplicity() );

  CHECK( 0 == delayed.NB() );
  CHECK( 4 == delayed.NE() );
  CHECK_THAT( 1e-11, WithinRel( delayed.energies().front() ) );
  CHECK_THAT( 30., WithinRel( delayed.energies().back() ) );
  CHECK_THAT( 0.044, WithinRel( delayed.multiplicities().front() ) );
  CHECK_THAT( 0.026, WithinRel( delayed.multiplicities().back() ) );

  // BDD block
  CHECK( false == chunk.BDD()->empty() );

  CHECK( 6 == chunk.BDD()->NPCR() );
  CHECK( 6 == chunk.BDD()->numberDelayedPrecursors() );

  CHECK_THAT( 1.249817E-10, WithinRel( chunk.BDD()->precursorGroupData( 1 ).DEC() ) );
  CHECK_THAT( 4.984604E-08, WithinRel( chunk.BDD()->precursorGroupData( 6 ).DEC() ) );

  // DNED block
  CHECK( false == chunk.DNED()->empty() );

  CHECK( 1 == chunk.DNED()->LDLW( 1 ) );
  CHECK( 4010 == chunk.DNED()->LDLW( 6 ) );

  CHECK( true == std::holds_alternative< OutgoingEnergyDistributionData >( chunk.DNED()->energyDistributionData( 1 ) ) );
  CHECK( true == std::holds_alternative< OutgoingEnergyDistributionData >( chunk.DNED()->energyDistributionData( 6 ) ) );

  CHECK( false == chunk.DNED()->referenceFrame( 1 ).has_value() );
  CHECK( false == chunk.DNED()->referenceFrame( 6 ).has_value() );

  // PTYPE block
  CHECK( false == chunk.PTYPE().has_value() );

  // NTRO block
  CHECK( false == chunk.NTRO().has_value() );

  // IXS block
  CHECK( false == chunk.IXS().has_value() );
}
