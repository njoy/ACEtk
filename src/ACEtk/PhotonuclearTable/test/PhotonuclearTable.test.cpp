// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/PhotonuclearTable.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::ACEtk;
using DistributionGivenElsewhere = continuous::DistributionGivenElsewhere;
using EnergyAngleDistributionData = continuous::EnergyAngleDistributionData;

void verifyChunk( const PhotonuclearTable& );

SCENARIO( "PhotonuclearTable" ){

  GIVEN( "valid data for a PhotonuclearTable prior to NJOY2016.75" ) {

    auto table = fromFile( "94239.31u" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a PhotonuclearTable from a table" ) {

      PhotonuclearTable chunk( std::move( table ) );

      THEN( "a PhotonuclearTable can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
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
            case  9 : { CHECK(     94 == nxs_chunk[i] ); break; }
            case 10 : { CHECK(    239 == nxs_chunk[i] ); break; }
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

    WHEN( "constructing a PhotonuclearTable from its components" ) {

      PhotonuclearTable base( std::move( table ) );

      std::optional< std::vector< unsigned int > > ptype = std::vector< unsigned int >{};
      std::optional< std::vector< continuous::CrossSectionData > > pxs = std::vector< continuous::CrossSectionData >{};
      std::optional< std::vector< continuous::CrossSectionData > > phn = std::vector< continuous::CrossSectionData >{};
      std::optional< std::vector< continuous::MTRH > > mtrh = std::vector< continuous::MTRH >{};
      std::optional< std::vector< continuous::SIGH > > sigh = std::vector< continuous::SIGH >{};
      std::optional< std::vector< continuous::ANDH > > andh = std::vector< continuous::ANDH >{};
      std::optional< std::vector< continuous::DLWH > > dlwh = std::vector< continuous::DLWH >{};
      for ( unsigned int index = 1; index <= base.NTYPE(); ++index ) {

        ptype->push_back( base.IXS()->IP( index ) );
        pxs->push_back( base.PXS( index ) );
        phn->push_back( base.PHN( index ) );
        mtrh->push_back( base.MTRH( index ) );
        sigh->push_back( base.SIGH( index ) );
        andh->push_back( base.ANDH( index ) );
        dlwh->push_back( base.DLWH( index ) );
      }

      PhotonuclearTable chunk( 94, 239, 0, base.header(),
                               base.ESZ(), base.MTR(), base.LQR(),
                               base.SIG(), std::move( ptype ),
                               std::move( pxs ), std::move( phn ),
                               std::move( mtrh ), std::move( sigh ),
                               std::move( andh ), std::move( dlwh ) );

      THEN( "a PhotonuclearTable can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
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
            case  9 : { CHECK(     94 == nxs_chunk[i] ); break; }
            case 10 : { CHECK(    239 == nxs_chunk[i] ); break; }
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
  } // GIVEN
} // SCENARIO

void verifyChunk( const PhotonuclearTable& chunk ) {

  CHECK( "94239.31u" == chunk.ZAID() );
  CHECK_THAT( 0.0, WithinRel( chunk.temperature() ) );

  CHECK( 1038009 == chunk.length() );
  CHECK( 94239 == chunk.ZA() );
  CHECK( 90 == chunk.NES() );
  CHECK( 90 == chunk.numberEnergyPoints() );
  CHECK( 2 == chunk.NTR() );
  CHECK( 2 == chunk.numberReactions() );
  CHECK( 7 == chunk.NTYPE() );
  CHECK( 7 == chunk.numberSecondaryParticleTypes() );
  CHECK( 0 == chunk.S() );
  CHECK( 0 == chunk.isomericState() );
  CHECK( 94 == chunk.Z() );
  CHECK( 94 == chunk.atomNumber() );
  CHECK( 239 == chunk.A() );
  CHECK( 239 == chunk.massNumber() );

  // ESZ block
  CHECK( false == chunk.ESZ().empty() );
  CHECK( 90 == chunk.ESZ().energies().size() );
  CHECK( 90 == chunk.ESZ().total().size() );
  CHECK( 0 == chunk.ESZ().elastic().size() );
  CHECK( 90 == chunk.ESZ().heating().size() );

  CHECK_THAT( 1., WithinRel( chunk.ESZ().energies().front() ) );
  CHECK_THAT( 200., WithinRel( chunk.ESZ().energies().back() ) );

  CHECK_THAT( 1., WithinRel( chunk.ESZ().XSS( 1 ) ) );
  CHECK_THAT( 200., WithinRel( chunk.ESZ().XSS( 90 ) ) );

  // MTR block
  CHECK( false == chunk.MTR().empty() );
  CHECK( 2 == chunk.MTR().MTs().size() );
  CHECK( 5 == chunk.MTR().MTs().front() );
  CHECK( 18 == chunk.MTR().MTs().back() );
  CHECK( 2 == chunk.MTR().reactionNumbers().size() );
  CHECK( 5 == chunk.MTR().reactionNumbers().front() );
  CHECK( 18 == chunk.MTR().reactionNumbers().back() );

  CHECK( 5 == chunk.MTR().MT( 1 ) );
  CHECK( 18 == chunk.MTR().MT( 2 ) );
  CHECK( 5 == chunk.MTR().reactionNumber( 1 ) );
  CHECK( 18 == chunk.MTR().reactionNumber( 2 ) );

  CHECK( true == chunk.MTR().hasReactionNumber( 5 ) );
  CHECK( true == chunk.MTR().hasReactionNumber( 18 ) );
  CHECK( 1 == chunk.MTR().index( 5 ) );
  CHECK( 2 == chunk.MTR().index( 18 ) );

  // LQR block
  CHECK( false == chunk.LQR().empty() );
  CHECK( 2 == chunk.LQR().QValues().size() );
  CHECK_THAT( 0., WithinRel( chunk.LQR().QValues().front() ) );
  CHECK_THAT( 199.188, WithinRel( chunk.LQR().QValues().back() ) );

  CHECK_THAT( 0., WithinRel( chunk.LQR().QValue( 1 ) ) );
  CHECK_THAT( 199.188, WithinRel( chunk.LQR().QValue( 2 ) ) );

  // SIG block
  CHECK( false == chunk.SIG().empty() );
  CHECK( 2 == chunk.SIG().NTR() );

  CHECK( 1 == chunk.SIG().LSIG( 1 ) );
  CHECK( 93 == chunk.SIG().LSIG( 2 ) );

  CHECK( 1 == chunk.SIG().energyIndex( 1 ) );
  CHECK( 3 == chunk.SIG().energyIndex( 2 ) );

  CHECK( 90 == chunk.SIG().numberValues( 1 ) );
  CHECK( 88 == chunk.SIG().numberValues( 2 ) );

  auto xs1 = chunk.SIG().crossSectionData( 1 );
  auto xs2 = chunk.SIG().crossSectionData( 2 );
  CHECK( 1 == xs1.energyIndex() );
  CHECK( 3 == xs2.energyIndex() );
  CHECK( 90 == xs1.numberValues() );
  CHECK( 88 == xs2.numberValues() );
  CHECK_THAT( 0., WithinRel( xs1.crossSections().front() ) );
  CHECK_THAT( 3.35584000000E-04, WithinRel( xs1.crossSections().back() ) );
  CHECK_THAT( 0., WithinRel( xs2.crossSections().front() ) );
  CHECK_THAT( 6.65666700000E-03, WithinRel( xs2.crossSections().back() ) );

  auto data1 = chunk.SIG().crossSections( 1 );
  auto data2 = chunk.SIG().crossSections( 2 );
  CHECK( 90 == data1.size() );
  CHECK( 88 == data2.size() );
  CHECK_THAT( 0., WithinRel( data1.front() ) );
  CHECK_THAT( 3.35584000000E-04, WithinRel( data1.back() ) );
  CHECK_THAT( 0., WithinRel( data2.front() ) );
  CHECK_THAT( 6.65666700000E-03, WithinRel( data2.back() ) );

  // IXSU block
  CHECK( false == chunk.IXS()->empty() );

  CHECK( 7 == chunk.IXS()->NTYPE() );
  CHECK( 7 == chunk.IXS()->numberAdditionalSecondaryParticleTypes() );

  CHECK( 1 == chunk.IXS()->IP( 1 ) );
  CHECK( 2 == chunk.IXS()->IP( 2 ) );
  CHECK( 9 == chunk.IXS()->IP( 3 ) );
  CHECK( 31 == chunk.IXS()->IP( 4 ) );
  CHECK( 32 == chunk.IXS()->IP( 5 ) );
  CHECK( 33 == chunk.IXS()->IP( 6 ) );
  CHECK( 34 == chunk.IXS()->IP( 7 ) );

  CHECK( 2 == chunk.IXS()->NP( 1 ) );
  CHECK( 1 == chunk.IXS()->NP( 2 ) );
  CHECK( 1 == chunk.IXS()->NP( 3 ) );
  CHECK( 1 == chunk.IXS()->NP( 4 ) );
  CHECK( 1 == chunk.IXS()->NP( 5 ) );
  CHECK( 1 == chunk.IXS()->NP( 6 ) );
  CHECK( 1 == chunk.IXS()->NP( 7 ) );

  CHECK( 543 == chunk.IXS()->PXS( 1 ) );
  CHECK( 635 == chunk.IXS()->PHN( 1 ) );
  CHECK( 727 == chunk.IXS()->MTRH( 1 ) );
  CHECK( 729 == chunk.IXS()->TYRH( 1 ) );
  CHECK( 731 == chunk.IXS()->LSIGH( 1 ) );
  CHECK( 733 == chunk.IXS()->SIGH( 1 ) );
  CHECK( 1085 == chunk.IXS()->LANDH( 1 ) );
  CHECK( 1087 == chunk.IXS()->ANDH( 1 ) );
  CHECK( 1087 == chunk.IXS()->LDLWH( 1 ) );
  CHECK( 1089 == chunk.IXS()->DLWH( 1 ) );

  CHECK( 863286 == chunk.IXS()->PXS( 7 ) );
  CHECK( 863378 == chunk.IXS()->PHN( 7 ) );
  CHECK( 863470 == chunk.IXS()->MTRH( 7 ) );
  CHECK( 863471 == chunk.IXS()->TYRH( 7 ) );
  CHECK( 863472 == chunk.IXS()->LSIGH( 7 ) );
  CHECK( 863473 == chunk.IXS()->SIGH( 7 ) );
  CHECK( 863657 == chunk.IXS()->LANDH( 7 ) );
  CHECK( 863658 == chunk.IXS()->ANDH( 7 ) );
  CHECK( 863658 == chunk.IXS()->LDLWH( 7 ) );
  CHECK( 863659 == chunk.IXS()->DLWH( 7 ) );

  // PXS(1) block
  CHECK( false == chunk.PXS(1).empty() );

  CHECK( 1 == chunk.PXS(1).energyIndex() );
  CHECK( 90 == chunk.PXS(1).numberValues() );
  CHECK_THAT( 0.00000000000E+00, WithinRel( chunk.PXS(1).crossSections().front() ) );
  CHECK_THAT( 1.21479700000E-01, WithinRel( chunk.PXS(1).crossSections().back() ) );

  // PHN(1) block
  CHECK( false == chunk.PHN(1).empty() );

  CHECK( 1 == chunk.PHN(1).energyIndex() );
  CHECK( 90 == chunk.PHN(1).numberValues() );
  CHECK_THAT( 0.00000000000E+00, WithinRel( chunk.PHN(1).crossSections().front() ) );
  CHECK_THAT( 7.91132000000E+01, WithinRel( chunk.PHN(1).crossSections().back() ) );

  // MTRH(1) block
  CHECK( false == chunk.MTRH(1).empty() );
  CHECK( 2 == chunk.MTRH(1).NTR() );

  CHECK( 5 == chunk.MTRH(1).MT( 1 ) );
  CHECK( 18 == chunk.MTRH(1).MT( 2 ) );
  CHECK( 5 == chunk.MTRH(1).reactionNumber( 1 ) );
  CHECK( 18 == chunk.MTRH(1).reactionNumber( 2 ) );

  // TYRH(1) block
  CHECK( false == chunk.TYRH(1).empty() );
  CHECK( 2 == chunk.TYRH(1).NTR() );

  CHECK( ReferenceFrame::CentreOfMass == chunk.TYRH(1).referenceFrame( 1 ) );
  CHECK( ReferenceFrame::CentreOfMass == chunk.TYRH(1).referenceFrame( 2 ) );

  // SIGH(1) block
  CHECK( false == chunk.SIGH(1).empty() );
  CHECK( 2 == chunk.SIGH(1).NP() );

  auto multiplicity = chunk.SIGH(1).crossSectionData( 1 );
  CHECK( 6 == multiplicity.MFTYPE() );
  CHECK( 6 == multiplicity.type() );
  CHECK( 5 == multiplicity.MT() );
  CHECK( 5 == multiplicity.reactionNumber() );

  CHECK( 0 == multiplicity.interpolationData().NB() );

  CHECK( 84 == multiplicity.NE() );
  CHECK( 84 == multiplicity.numberValues() );

  CHECK( 84 == multiplicity.energies().size() );
  CHECK_THAT( 1.00000000000E+00, WithinRel( multiplicity.energies().front() ) );
  CHECK_THAT( 2.00000000000E+02, WithinRel( multiplicity.energies().back() ) );

  CHECK( 84 == multiplicity.multiplicities().size() );
  CHECK_THAT( 0.00000000000E+00, WithinRel( multiplicity.multiplicities().front() ) );
  CHECK_THAT( 1.26229500000E+02, WithinRel( multiplicity.multiplicities().back() ) );

  multiplicity = chunk.SIGH(1).crossSectionData( 2 );
  CHECK( 6 == multiplicity.MFTYPE() );
  CHECK( 6 == multiplicity.type() );
  CHECK( 18 == multiplicity.MT() );
  CHECK( 18 == multiplicity.reactionNumber() );

  CHECK( 0 == multiplicity.interpolationData().NB() );

  CHECK( 88 == multiplicity.NE() );
  CHECK( 88 == multiplicity.numberValues() );

  CHECK( 88 == multiplicity.energies().size() );
  CHECK_THAT( 1.00000000000E+00, WithinRel( multiplicity.energies().front() ) );
  CHECK_THAT( 2.00000000000E+02, WithinRel( multiplicity.energies().back() ) );

  CHECK( 88 == multiplicity.multiplicities().size() );
  CHECK_THAT( 1.94030000000E+00, WithinRel( multiplicity.multiplicities().front() ) );
  CHECK_THAT( 1.18857000000E+01, WithinRel( multiplicity.multiplicities().back() ) );

  // ANDH(1) block
  CHECK( false == chunk.ANDH(1).empty() );
  CHECK( 2 == chunk.ANDH(1).NR() );

  CHECK( true == std::holds_alternative< DistributionGivenElsewhere >( chunk.ANDH(1).angularDistributionData( 1 ) ) );
  CHECK( true == std::holds_alternative< DistributionGivenElsewhere >( chunk.ANDH(1).angularDistributionData( 2 ) ) );

  // DLWH(1) block
  CHECK( false == chunk.DLWH(1).empty() );
  CHECK( 2 == chunk.DLWH(1).NR() );

  CHECK( true == std::holds_alternative< EnergyAngleDistributionData >( chunk.DLWH(1).energyDistributionData( 1 ) ) );
  CHECK( true == std::holds_alternative< EnergyAngleDistributionData >( chunk.DLWH(1).energyDistributionData( 2 ) ) );

  // PXS(7) block
  CHECK( false == chunk.PXS(7).empty() );

  CHECK( 1 == chunk.PXS(7).energyIndex() );
  CHECK( 90 == chunk.PXS(7).numberValues() );
  CHECK_THAT( 0.00000000000E+00, WithinRel( chunk.PXS(7).crossSections().front() ) );
  CHECK_THAT( 1.63503800000E-03, WithinRel( chunk.PXS(7).crossSections().back() ) );

  // PHN(7) block
  CHECK( false == chunk.PHN(7).empty() );

  CHECK( 1 == chunk.PHN(7).energyIndex() );
  CHECK( 90 == chunk.PHN(7).numberValues() );
  CHECK_THAT( 0.00000000000E+00, WithinRel( chunk.PHN(7).crossSections().front() ) );
  CHECK_THAT( 5.97042200000E+00, WithinRel( chunk.PHN(7).crossSections().back() ) );

  // MTRH(7) block
  CHECK( false == chunk.MTRH(7).empty() );
  CHECK( 1 == chunk.MTRH(7).NTR() );

  CHECK( 5 == chunk.MTRH(7).MT( 1 ) );
  CHECK( 5 == chunk.MTRH(7).reactionNumber( 1 ) );

  // TYRH(7) block
  CHECK( false == chunk.TYRH(7).empty() );
  CHECK( 1 == chunk.TYRH(7).NTR() );

  CHECK( ReferenceFrame::CentreOfMass == chunk.TYRH(7).referenceFrame( 1 ) );

  // SIGH(7) block
  CHECK( false == chunk.SIGH(7).empty() );
  CHECK( 1 == chunk.SIGH(7).NP() );

  multiplicity = chunk.SIGH(7).crossSectionData( 1 );
  CHECK( 6 == multiplicity.MFTYPE() );
  CHECK( 6 == multiplicity.type() );
  CHECK( 5 == multiplicity.MT() );
  CHECK( 5 == multiplicity.reactionNumber() );

  CHECK( 0 == multiplicity.interpolationData().NB() );

  CHECK( 90 == multiplicity.NE() );
  CHECK( 90 == multiplicity.numberValues() );

  CHECK( 90 == multiplicity.energies().size() );
  CHECK_THAT( 1.00000000000E+00, WithinRel( multiplicity.energies().front() ) );
  CHECK_THAT( 2.00000000000E+02, WithinRel( multiplicity.energies().back() ) );

  CHECK( 90 == multiplicity.multiplicities().size() );
  CHECK_THAT( 5.08021000000E-19, WithinRel( multiplicity.multiplicities().front() ) );
  CHECK_THAT( 4.87221700000E+00, WithinRel( multiplicity.multiplicities().back() ) );

  // ANDH(7) block
  CHECK( false == chunk.ANDH(7).empty() );
  CHECK( 1 == chunk.ANDH(7).NR() );

  CHECK( true == std::holds_alternative< DistributionGivenElsewhere >( chunk.ANDH(7).angularDistributionData( 1 ) ) );

  // DLWH(7) block
  CHECK( false == chunk.DLWH(7).empty() );
  CHECK( 1 == chunk.DLWH(7).NR() );

  CHECK( true == std::holds_alternative< EnergyAngleDistributionData >( chunk.DLWH(7).energyDistributionData( 1 ) ) );
}
