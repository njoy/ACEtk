#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/fromFile.hpp"
#include "ACEtk/ThermalScatteringTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

void verifyChunkH2O( const ThermalScatteringTable& );
void verifyChunkZrZrH( const ThermalScatteringTable& );
void verifyChunkAl( const ThermalScatteringTable& );
void verifyChunkDLiD( const ThermalScatteringTable& );

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

  GIVEN( "valid data for a ThermalScatteringTable - Zr-ZrH" ) {

    auto table = fromFile( "zr-zrh.40t" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a ThermalScatteringTable from a table" ) {

      ThermalScatteringTable chunk( std::move( table ) );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkZrZrH( chunk );
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

  GIVEN( "valid data for a ThermalScatteringTable - Al" ) {

    auto table = fromFile( "al-27.40t" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a ThermalScatteringTable from a table" ) {

      ThermalScatteringTable chunk( std::move( table ) );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkAl( chunk );
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

  GIVEN( "valid data for a ThermalScatteringTable - D-LiD" ) {

    auto table = fromFile( "d-lid.10t" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a ThermalScatteringTable from a table" ) {

      ThermalScatteringTable chunk( std::move( table ) );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkDLiD( chunk );
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

  // ITIE block
  CHECK( false == chunk.ITIE().empty() );

  CHECK( 118 == chunk.ITIE().NE() );
  CHECK( 118 == chunk.ITIE().numberEnergies() );

  CHECK( 118 == chunk.ITIE().energies().size() );
  CHECK( 1e-11 == Approx( chunk.ITIE().energies().front() ) );
  CHECK( 1e-5 == Approx( chunk.ITIE().energies().back() ) );

  CHECK( 118 == chunk.ITIE().crossSections().size() );
  CHECK( 500.5451 == Approx( chunk.ITIE().crossSections().front() ) );
  CHECK( 20.53782 == Approx( chunk.ITIE().crossSections().back() ) );

  // ITCE block
  CHECK( true == chunk.ITCE().empty() );

  // ITCEI block
  CHECK( true == chunk.ITCEI().empty() );
}

void verifyChunkZrZrH( const ThermalScatteringTable& chunk ) {

  CHECK( "zr-zrh.40t" == chunk.ZAID() );
  CHECK( 2.53e-8 == Approx( chunk.temperature() ) );

  CHECK( 1091556 == chunk.length() );
  CHECK( 3 == chunk.IDPNI() );
  CHECK( 3 == chunk.inelasticScatteringMode() );
  CHECK( 21 == chunk.NIL() );
  CHECK( 21 == chunk.inelasticDimensioningParameter() );
  CHECK( 80 == chunk.NIEB() );
  CHECK( 80 == chunk.numberInelasticOutgoingEnergies() );
  CHECK( 3 == chunk.IDPNC() );
  CHECK( 3 == chunk.elasticScatteringMode() );
  CHECK( 19 == chunk.NCL() );
  CHECK( 19 == chunk.firstElasticDimensioningParameter() );
  CHECK( 0 == chunk.NCLI() );
  CHECK( 0 == chunk.secondElasticDimensioningParameter() );
  CHECK( 2 == chunk.IFENG() );
  CHECK( 2 == chunk.secondaryEnergyMode() );

  // ITIE block
  CHECK( false == chunk.ITIE().empty() );

  CHECK( 91 == chunk.ITIE().NE() );
  CHECK( 91 == chunk.ITIE().numberEnergies() );

  CHECK( 91 == chunk.ITIE().energies().size() );
  CHECK( 1e-11 == Approx( chunk.ITIE().energies().front() ) );
  CHECK( 9.5e-7 == Approx( chunk.ITIE().energies().back() ) );

  CHECK( 91 == chunk.ITIE().crossSections().size() );
  CHECK( 2.619597 == Approx( chunk.ITIE().crossSections().front() ) );
  CHECK( 5.3698962 == Approx( chunk.ITIE().crossSections().back() ) );

  // ITCE block
  CHECK( true == chunk.ITCE().empty() );

  // ITCEI block
  CHECK( false == chunk.ITCEI().empty() );

  CHECK( 91 == chunk.ITCEI().NE() );
  CHECK( 91 == chunk.ITCEI().numberEnergies() );

  CHECK( 91 == chunk.ITCEI().energies().size() );
  CHECK( 1e-11 == Approx( chunk.ITCEI().energies().front() ) );
  CHECK( 9.5e-7 == Approx( chunk.ITCEI().energies().back() ) );

  CHECK( 91 == chunk.ITCEI().crossSections().size() );
  CHECK( 6.337617 == Approx( chunk.ITCEI().crossSections().front() ) );
  CHECK( 0.82849246 == Approx( chunk.ITCEI().crossSections().back() ) );
}

void verifyChunkAl( const ThermalScatteringTable& chunk ) {

  CHECK( "al-27.40t" == chunk.ZAID() );
  CHECK( 2.53e-8 == Approx( chunk.temperature() ) );

  CHECK( 1066414 == chunk.length() );
  CHECK( 3 == chunk.IDPNI() );
  CHECK( 3 == chunk.inelasticScatteringMode() );
  CHECK( 21 == chunk.NIL() );
  CHECK( 21 == chunk.inelasticDimensioningParameter() );
  CHECK( 80 == chunk.NIEB() );
  CHECK( 80 == chunk.numberInelasticOutgoingEnergies() );
  CHECK( 4 == chunk.IDPNC() );
  CHECK( 4 == chunk.elasticScatteringMode() );
  CHECK( -1 == chunk.NCL() );
  CHECK( -1 == chunk.firstElasticDimensioningParameter() );
  CHECK( 0 == chunk.NCLI() );
  CHECK( 0 == chunk.secondElasticDimensioningParameter() );
  CHECK( 2 == chunk.IFENG() );
  CHECK( 2 == chunk.secondaryEnergyMode() );

  // ITIE block
  CHECK( false == chunk.ITIE().empty() );

  CHECK( 100 == chunk.ITIE().NE() );
  CHECK( 100 == chunk.ITIE().numberEnergies() );

  CHECK( 100 == chunk.ITIE().energies().size() );
  CHECK( 1e-11 == Approx( chunk.ITIE().energies().front() ) );
  CHECK( 2.18e-6 == Approx( chunk.ITIE().energies().back() ) );

  CHECK( 100 == chunk.ITIE().crossSections().size() );
  CHECK( 1.677347 == Approx( chunk.ITIE().crossSections().front() ) );
  CHECK( 1.31533352198 == Approx( chunk.ITIE().crossSections().back() ) );

  // ITCE block
  CHECK( false == chunk.ITCE().empty() );

  CHECK( 119 == chunk.ITCE().NE() );
  CHECK( 119 == chunk.ITCE().numberEnergies() );

  CHECK( 119 == chunk.ITCE().energies().size() );
  CHECK( 3.759019e-9 == Approx( chunk.ITCE().energies().front() ) );
  CHECK( 5.813947e-7 == Approx( chunk.ITCE().energies().back() ) );

  CHECK( 119 == chunk.ITCE().crossSections().size() );
  CHECK( 5.10384187842E-09 == Approx( chunk.ITCE().crossSections().front() ) );
  CHECK( 7.15617224626E-08 == Approx( chunk.ITCE().crossSections().back() ) );

  // ITCEI block
  CHECK( true == chunk.ITCEI().empty() );
}

void verifyChunkDLiD( const ThermalScatteringTable& chunk ) {

  CHECK( "d-lid.10t" == chunk.ZAID() );
  CHECK( 2.53e-8 == Approx( chunk.temperature() ) );

  CHECK( 52095 == chunk.length() );
  CHECK( 3 == chunk.IDPNI() );
  CHECK( 3 == chunk.inelasticScatteringMode() );
  CHECK( 19 == chunk.NIL() );
  CHECK( 19 == chunk.inelasticDimensioningParameter() );
  CHECK( 20 == chunk.NIEB() );
  CHECK( 20 == chunk.numberInelasticOutgoingEnergies() );
  CHECK( 5 == chunk.IDPNC() );
  CHECK( 5 == chunk.elasticScatteringMode() );
  CHECK( -1 == chunk.NCL() );
  CHECK( -1 == chunk.firstElasticDimensioningParameter() );
  CHECK( 19 == chunk.NCLI() );
  CHECK( 19 == chunk.secondElasticDimensioningParameter() );
  CHECK( 1 == chunk.IFENG() );
  CHECK( 1 == chunk.secondaryEnergyMode() );

  // ITIE block
  CHECK( false == chunk.ITIE().empty() );

  CHECK( 117 == chunk.ITIE().NE() );
  CHECK( 117 == chunk.ITIE().numberEnergies() );

  CHECK( 117 == chunk.ITIE().energies().size() );
  CHECK( 1e-11 == Approx( chunk.ITIE().energies().front() ) );
  CHECK( 9.85e-6 == Approx( chunk.ITIE().energies().back() ) );

  CHECK( 117 == chunk.ITIE().crossSections().size() );
  CHECK( 14.55274 == Approx( chunk.ITIE().crossSections().front() ) );
  CHECK( 1.68978156625 == Approx( chunk.ITIE().crossSections().back() ) );

  // ITCE block
  CHECK( false == chunk.ITCE().empty() );

  CHECK( 72 == chunk.ITCE().NE() );
  CHECK( 72 == chunk.ITCE().numberEnergies() );

  CHECK( 72 == chunk.ITCE().energies().size() );
  CHECK( 3.70672e-9 == Approx( chunk.ITCE().energies().front() ) );
  CHECK( 3.66965e-7 == Approx( chunk.ITCE().energies().back() ) );

  CHECK( 72 == chunk.ITCE().crossSections().size() );
  CHECK( 3.75735379520E-09 == Approx( chunk.ITCE().crossSections().front() ) );
  CHECK( 8.39439776800E-08 == Approx( chunk.ITCE().crossSections().back() ) );

  // ITCEI block
  CHECK( false == chunk.ITCEI().empty() );

  CHECK( 117 == chunk.ITCEI().NE() );
  CHECK( 117 == chunk.ITCEI().numberEnergies() );

  CHECK( 117 == chunk.ITCEI().energies().size() );
  CHECK( 1e-11 == Approx( chunk.ITCEI().energies().front() ) );
  CHECK( 9.85e-6 == Approx( chunk.ITCEI().energies().back() ) );

  CHECK( 117 == chunk.ITCEI().crossSections().size() );
  CHECK( 1.026886 == Approx( chunk.ITCEI().crossSections().front() ) );
  CHECK( 2.48815555289E-03 == Approx( chunk.ITCEI().crossSections().back() ) );
}
