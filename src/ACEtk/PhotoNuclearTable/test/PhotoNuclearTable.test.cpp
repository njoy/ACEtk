#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoNuclearTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

void verifyChunk( const PhotoNuclearTable& );

SCENARIO( "PhotoNuclearTable" ){

  GIVEN( "valid data for a PhotoNuclearTable" ) {

    auto table = fromFile( "94239.31u" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a PhotoNuclearTable from a table" ) {

      PhotoNuclearTable chunk( std::move( table ) );

      THEN( "a PhotoNuclearTable can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      }

      THEN( "the IZ array is correct" ) {

        decltype(auto) iz_chunk = chunk.data().IZ();
        CHECK( iz.size() == iz_chunk.size() );
        for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {

          CHECK( iz[i] == Approx( iz_chunk[i] ) );
        }
      } // THEN

      THEN( "the AW array is correct" ) {

        decltype(auto) aw_chunk = chunk.data().AW();
        CHECK( aw.size() == aw_chunk.size() );
        for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {

          CHECK( aw[i] == Approx( aw_chunk[i] ) );
        }
      } // THEN

      THEN( "the NXS array is correct" ) {

        decltype(auto) nxs_chunk = chunk.data().NXS();
        CHECK( nxs.size() == nxs_chunk.size() );
        for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {

          CHECK( nxs[i] == Approx( nxs_chunk[i] ) );
        }
      } // THEN

      THEN( "the JXS array is correct" ) {

        decltype(auto) jxs_chunk = chunk.data().JXS();
        CHECK( jxs.size() == jxs_chunk.size() );
        for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {

          CHECK( jxs[i] == Approx( jxs_chunk[i] ) );
        }
      } // THEN

      THEN( "the XSS array is correct" ) {

        decltype(auto) xss_chunk = chunk.data().XSS();
        CHECK( xss.size() == xss_chunk.size() );
        for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

//    WHEN( "constructing a PhotoNuclearTable from its components" ) {
//
//      PhotoNuclearTable base( std::move( table ) );
//
//      PhotoNuclearTable chunk( 92, 235, base.header(),
//                                   base.ESZ(), base.NU(), base.DNU(),
//                                   base.MTR(), base.LQR(),
//                                   base.SIG(), base.AND(), base.DLW(),
//                                   base.BDD(), base.DNED(),
//                                   base.GPD(), base.MTRP(), base.SIGP(),
//                                   base.ANDP(), base.DLWP(), base.YP(),
//                                   base.UNR(),
//                                   std::nullopt, std::nullopt, std::nullopt,
//                                   std::nullopt, std::nullopt, std::nullopt,
//                                   std::nullopt );
//
//      THEN( "a PhotoNuclearTable can be constructed and members can be "
//            "tested" ) {
//
//        verifyChunk( chunk );
//      }
//
//      THEN( "the IZ array is correct" ) {
//
//        decltype(auto) iz_chunk = chunk.data().IZ();
//        CHECK( iz.size() == iz_chunk.size() );
//        for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {
//
//          CHECK( iz[i] == Approx( iz_chunk[i] ) );
//        }
//      } // THEN
//
//      THEN( "the AW array is correct" ) {
//
//        decltype(auto) aw_chunk = chunk.data().AW();
//        CHECK( aw.size() == aw_chunk.size() );
//        for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {
//
//          CHECK( aw[i] == Approx( aw_chunk[i] ) );
//        }
//      } // THEN
//
//      THEN( "the NXS array is correct" ) {
//
//        decltype(auto) nxs_chunk = chunk.data().NXS();
//        CHECK( nxs.size() == nxs_chunk.size() );
//        for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {
//
//          CHECK( nxs[i] == Approx( nxs_chunk[i] ) );
//        }
//      } // THEN
//
//      THEN( "the JXS array is correct" ) {
//
//        decltype(auto) jxs_chunk = chunk.data().JXS();
//        CHECK( jxs.size() == jxs_chunk.size() );
//        for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {
//
//          CHECK( jxs[i] == Approx( jxs_chunk[i] ) );
//        }
//      } // THEN
//
//      THEN( "the XSS array is correct" ) {
//
//        decltype(auto) xss_chunk = chunk.data().XSS();
//        CHECK( xss.size() == xss_chunk.size() );
//        for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {
//
//          CHECK( xss[i] == Approx( xss_chunk[i] ) );
//        }
//      } // THEN
//    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const PhotoNuclearTable& chunk ) {

  CHECK( "94239.31u" == chunk.ZAID() );
  CHECK( 0.0 == Approx( chunk.temperature() ) );

  CHECK( 1038009 == chunk.length() );
  CHECK( 94239 == chunk.ZA() );
  CHECK( 90 == chunk.NES() );
  CHECK( 90 == chunk.numberEnergyPoints() );
  CHECK( 2 == chunk.NTR() );
  CHECK( 2 == chunk.numberReactions() );
  CHECK( 7 == chunk.NTYPE() );
  CHECK( 7 == chunk.numberSecondaryParticleTypes() );

  // ESZ block
  CHECK( false == chunk.ESZ().empty() );
  CHECK( 90 == chunk.ESZ().energies().size() );
  CHECK( 90 == chunk.ESZ().total().size() );
  CHECK( 0 == chunk.ESZ().elastic().size() );
  CHECK( 90 == chunk.ESZ().heating().size() );

  CHECK( 1. == Approx( chunk.ESZ().energies().front() ) );
  CHECK( 200. == Approx( chunk.ESZ().energies().back() ) );

  CHECK( 1. == Approx( chunk.ESZ().XSS( 1 ) ) );
  CHECK( 90 == chunk.ESZ().XSS( 1, chunk.NES() ).size() );

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
  CHECK( 0. == chunk.LQR().QValues().front() );
  CHECK( 199.188 == Approx( chunk.LQR().QValues().back() ) );

  CHECK( 0. == chunk.LQR().QValue( 1 ) );
  CHECK( 199.188 == Approx( chunk.LQR().QValue( 2 ) ) );

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
  CHECK( 0. == Approx( xs1.crossSections().front() ) );
  CHECK( 3.35584000000E-04 == Approx( xs1.crossSections().back() ) );
  CHECK( 0. == Approx( xs2.crossSections().front() ) );
  CHECK( 6.65666700000E-03 == Approx( xs2.crossSections().back() ) );

  auto data1 = chunk.SIG().crossSections( 1 );
  auto data2 = chunk.SIG().crossSections( 2 );
  CHECK( 90 == data1.size() );
  CHECK( 88 == data2.size() );
  CHECK( 0. == Approx( data1.front() ) );
  CHECK( 3.35584000000E-04 == Approx( data1.back() ) );
  CHECK( 0. == Approx( data2.front() ) );
  CHECK( 6.65666700000E-03 == Approx( data2.back() ) );
}
