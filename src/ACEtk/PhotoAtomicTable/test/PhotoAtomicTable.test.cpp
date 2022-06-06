#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoAtomicTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

void verifyChunk( const PhotoAtomicTable& );

SCENARIO( "PhotoAtomicTable" ){

  GIVEN( "valid data for a PhotoAtomicTable - mcplib" ) {

    auto table = fromFile( "1000.01p" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a PhotoAtomicTable from a table" ) {

      PhotoAtomicTable chunk( std::move( table ) );

      THEN( "a PhotoAtomicTable can be constructed and members can be "
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

    WHEN( "constructing a PhotoAtomicTable from its components" ) {

      PhotoAtomicTable base( std::move( table ) );

      PhotoAtomicTable chunk( base.header(),
                              { 1001, 1002, 1003 },
                              { 0.999167, 1.996800, 2.990140 },
                              base.ESZG(), base.JINC(),
                              base.JCOH(), base.LHNM() );

      THEN( "a PhotoAtomicTable can be constructed and members can be "
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
  } // GIVEN
} // SCENARIO

void verifyChunk( const PhotoAtomicTable& chunk ) {

  CHECK( "1000.01p" == chunk.ZAID() );
  CHECK( 0. == Approx( chunk.temperature() ) );

  CHECK( 389 == chunk.length() );
  CHECK( 43 == chunk.NES() );
  CHECK( 43 == chunk.numberEnergyPoints() );

  // ESZG block
  CHECK( false == chunk.ESZG().empty() );

  CHECK( 43 == chunk.ESZG().NES() );
  CHECK( 43 == chunk.ESZG().numberEnergyPoints() );

  CHECK( 43 == chunk.ESZG().energies().size() );
  CHECK( 43 == chunk.ESZG().incoherent().size() );
  CHECK( 43 == chunk.ESZG().coherent().size() );
  CHECK( 43 == chunk.ESZG().photoelectric().size() );
  CHECK( 43 == chunk.ESZG().pairproduction().size() );

  CHECK( -6.907755278982E+00 == Approx( chunk.ESZG().energies().front() ) );
  CHECK(  4.605170185988E+00 == Approx( chunk.ESZG().energies().back() ) );
  CHECK( -2.474115088710E+00 == Approx( chunk.ESZG().incoherent().front() ) );
  CHECK( -4.794460770140E+00 == Approx( chunk.ESZG().incoherent().back() ) );
  CHECK( -5.438809818403E-01 == Approx( chunk.ESZG().coherent().front() ) );
  CHECK( -2.149558177385E+01 == Approx( chunk.ESZG().coherent().back() ) );
  CHECK(  2.449279472145E+00 == Approx( chunk.ESZG().photoelectric().front() ) );
  CHECK( -2.622629761934E+01 == Approx( chunk.ESZG().photoelectric().back() ) );
  CHECK(  0.000000000000E+00 == Approx( chunk.ESZG().pairproduction().front() ) );
  CHECK( -4.455371820900E+00 == Approx( chunk.ESZG().pairproduction().back() ) );

  // JINC block
  CHECK( false == chunk.JINC().empty() );

  CHECK( 21 == chunk.JINC().NM() );
  CHECK( 21 == chunk.JINC().numberValues() );

  CHECK( 21 == chunk.JINC().momentum().size() );
  CHECK( 0.   == Approx( chunk.JINC().momentum().front() ) );
  CHECK( 8.   == Approx( chunk.JINC().momentum().back() ) );

  CHECK( 21 == chunk.JINC().values().size() );
  CHECK( 0 == Approx( chunk.JINC().values().front() ) );
  CHECK( 1 == Approx( chunk.JINC().values().back() ) );

  // JCOH block
  CHECK( false == chunk.JCOH().empty() );

  CHECK( 55 == chunk.JCOH().NM() );
  CHECK( 55 == chunk.JCOH().numberValues() );

  CHECK( 55 == chunk.JCOH().momentum().size() );
  CHECK( 0.   == Approx( chunk.JCOH().momentum().front() ) );
  CHECK( 6.   == Approx( chunk.JCOH().momentum().back() ) );

  CHECK( 55 == chunk.JCOH().integratedFormFactors().size() );
  CHECK( 0. == Approx( chunk.JCOH().integratedFormFactors().front() ) );
  CHECK( 3.058316405266E-02 == Approx( chunk.JCOH().integratedFormFactors().back() ) );

  CHECK( 55 == chunk.JCOH().formFactors().size() );
  CHECK( 1. == Approx( chunk.JCOH().formFactors().front() ) );
  CHECK( 6.282390000000E-06 == Approx( chunk.JCOH().formFactors().back() ) );

  // LHNM block
  CHECK( false == chunk.LHNM().empty() );

  CHECK( 43 == chunk.LHNM().NES() );
  CHECK( 43 == chunk.LHNM().numberEnergyPoints() );
  CHECK( 43 == chunk.LHNM().heating().size() );

  CHECK( 9.457315870945E-04 == Approx( chunk.LHNM().heating().front() ) );
  CHECK( 9.086036433693E+01 == Approx( chunk.LHNM().heating().back() ) );
}
