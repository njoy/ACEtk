#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/fromFile.hpp"
#include "ACEtk/ThermalScatteringTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

void verifyChunkH2O( const ThermalScatteringTable& );

SCENARIO( "ThermalScatteringTable" ){

  GIVEN( "valid data for a ThermalScatteringTable - H2O" ) {

    auto table = fromFile( "h-h2o.40t" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a ThermalScatteringTable from a table" ) {

      ThermalScatteringTable chunk( std::move( table ) );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkH2O( chunk );
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

void verifyChunkH2O( const ThermalScatteringTable& chunk ) {

  CHECK( "h-h2o.40t" == chunk.ZAID() );
  CHECK( 2.53e-8 == Approx( chunk.temperature() ) );

  CHECK( 1643616 == chunk.length() );
  CHECK( 3 == chunk.IDPNI() );
  CHECK( 3 == chunk.inelasticScatteringMode() );
  CHECK( 21 == chunk.NIL() );
  CHECK( 21 == chunk.inelasticDimensioningParameter() );
  CHECK( 80 == chunk.NIEB() );
  CHECK( 80 == chunk.numberInelasticOutgoingEnergies() );
  CHECK( 0 == chunk.IDPNC() );
  CHECK( 0 == chunk.elasticScatteringMode() );
  CHECK( 0 == chunk.NCL() );
  CHECK( 0 == chunk.firstElasticDimensioningParameter() );
  CHECK( 0 == chunk.NCLI() );
  CHECK( 0 == chunk.secondElasticDimensioningParameter() );
  CHECK( 2 == chunk.IFENG() );
  CHECK( 2 == chunk.secondaryEnergyMode() );

}
