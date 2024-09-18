// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/ThermalScatteringTable.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::ACEtk;

void verifyChunkH2O( const ThermalScatteringTable& );
void verifyChunkZrZrH( const ThermalScatteringTable& );
void verifyChunkAl( const ThermalScatteringTable& );
void verifyChunkDLiD( const ThermalScatteringTable& );

SCENARIO( "ThermalScatteringTable" ){

  GIVEN( "valid data for a ThermalScatteringTable - H2O" ) {

    WHEN( "constructing a ThermalScatteringTable from a table" ) {

      auto table = fromFile( "h-h2o.40t" );
      ThermalScatteringTable chunk( std::move( table ) );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkH2O( chunk );
      } // THEN
    } // WHEN

    WHEN( "constructing a ThermalScatteringTable from its components" ) {

      ThermalScatteringTable base( fromFile( "h-h2o.40t" ) );

      ThermalScatteringTable chunk( base.header(), { 1001 },
                                    base.ITIE(), base.ITXE(),
                                    std::nullopt, std::nullopt,
                                    std::nullopt, std::nullopt );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkH2O( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ThermalScatteringTable - Zr-ZrH" ) {

    WHEN( "constructing a ThermalScatteringTable from a table" ) {

      auto table = fromFile( "zr-zrh.40t" );
      ThermalScatteringTable chunk( std::move( table ) );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkZrZrH( chunk );
      } // THEN
    } // WHEN

    WHEN( "constructing a ThermalScatteringTable from its components" ) {

      ThermalScatteringTable base( fromFile( "zr-zrh.40t" ) );

      ThermalScatteringTable chunk( base.header(),
                                    { 40090, 40091, 40092, 40094, 40096, 40000 },
                                    base.ITIE(), base.ITXE(),
                                    std::nullopt, std::nullopt,
                                    base.ITCEI(), base.ITCAI() );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkZrZrH( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ThermalScatteringTable - Al" ) {

    WHEN( "constructing a ThermalScatteringTable from a table" ) {

      auto table = fromFile( "al-27.40t" );
      ThermalScatteringTable chunk( std::move( table ) );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkAl( chunk );
      } // THEN
    } // WHEN

    WHEN( "constructing a ThermalScatteringTable from its components" ) {

      ThermalScatteringTable base( fromFile( "al-27.40t" ) );

      ThermalScatteringTable chunk( base.header(), { 13027 },
                                    base.ITIE(), base.ITXE(),
                                    base.ITCE(), base.ITCA(),
                                    std::nullopt, std::nullopt );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkAl( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a ThermalScatteringTable - D-LiD" ) {

    WHEN( "constructing a ThermalScatteringTable from a table" ) {

      auto table = fromFile( "d-lid.10t" );
      ThermalScatteringTable chunk( std::move( table ) );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkDLiD( chunk );
      } // THEN
    } // WHEN

    WHEN( "constructing a ThermalScatteringTable from its components" ) {

      ThermalScatteringTable base( fromFile( "d-lid.10t" ) );

      ThermalScatteringTable chunk( base.header(), { 1002 },
                                    base.ITIE(), base.ITXE(),
                                    base.ITCE(), base.ITCA(),
                                    base.ITCEI(), base.ITCAI() );

      THEN( "a ThermalScatteringTable can be constructed and members can be "
            "tested" ) {

        verifyChunkDLiD( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkH2O( const ThermalScatteringTable& chunk ) {

  auto table = fromFile( "h-h2o.40t" );
  std::array< int32_t, 16 > iz = table.data().IZ();
  std::array< double, 16 > aw = table.data().AW();
  std::array< int64_t, 16 > nxs = table.data().NXS();
  std::array< int64_t, 32 > jxs = table.data().JXS();
  std::vector< double > xss = table.data().XSS();

  // IZ, AW, NXS, JXS, XSS arrays

  decltype(auto) iz_chunk = chunk.data().IZ();
  CHECK( iz.size() == iz_chunk.size() );
  for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {

    CHECK( iz[i] == iz_chunk[i] );
  }

  decltype(auto) aw_chunk = chunk.data().AW();
  CHECK( aw.size() == aw_chunk.size() );
  for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {

    CHECK_THAT( aw[i], WithinRel( aw_chunk[i] ) );
  }

  decltype(auto) nxs_chunk = chunk.data().NXS();
  CHECK( nxs.size() == nxs_chunk.size() );
  for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {

    CHECK( nxs[i] == nxs_chunk[i] );
  }

  decltype(auto) jxs_chunk = chunk.data().JXS();
  CHECK( jxs.size() == jxs_chunk.size() );
  for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {

    CHECK( jxs[i] == jxs_chunk[i] );
  }

  decltype(auto) xss_chunk = chunk.data().XSS();
  CHECK( xss.size() == xss_chunk.size() );
  for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // ThermalScatteringTable interface

  CHECK( "h-h2o.40t" == chunk.ZAID() );
  CHECK_THAT( 2.53e-8, WithinRel( chunk.temperature() ) );

  CHECK( 1643616 == chunk.length() );
  CHECK( 3 == chunk.IDPNI() );
  CHECK( 3 == chunk.inelasticScatteringMode() );
  CHECK( 21 == chunk.NIL() );
  CHECK( 21 == chunk.inelasticDimensioningParameter() );
  CHECK( 0 == chunk.NIEB() );
  CHECK( 0 == chunk.numberInelasticOutgoingEnergies() );
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
  CHECK( 118 == chunk.ITIE().numberIncidentEnergies() );

  CHECK( 118 == chunk.ITIE().energies().size() );
  CHECK_THAT( 1e-11, WithinRel( chunk.ITIE().energies().front() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.ITIE().energies().back() ) );

  CHECK( 118 == chunk.ITIE().crossSections().size() );
  CHECK_THAT( 500.5451, WithinRel( chunk.ITIE().crossSections().front() ) );
  CHECK_THAT( 20.53782, WithinRel( chunk.ITIE().crossSections().back() ) );

  // ITXE block
  CHECK( false == chunk.ITXE().empty() );

  CHECK( 2 == chunk.ITXE().IFENG() );
  CHECK( 2 == chunk.ITXE().secondaryEnergyMode() );
  CHECK( 20 == chunk.ITXE().NC() );
  CHECK( 20 == chunk.ITXE().numberDiscreteCosines() );
  CHECK( 21 == chunk.ITXE().NIL() );
  CHECK( 21 == chunk.ITXE().inelasticDimensioningParameter() );
  CHECK( 118 == chunk.ITXE().NE() );
  CHECK( 118 == chunk.ITXE().numberIncidentEnergies() );

  // ITCE block
  CHECK( false == chunk.ITCE().has_value() );

  // ITCA block
  CHECK( false == chunk.ITCA().has_value() );

  // ITCEI block
  CHECK( false == chunk.ITCEI().has_value() );

  // ITCAI block
  CHECK( false == chunk.ITCAI().has_value() );
}

void verifyChunkZrZrH( const ThermalScatteringTable& chunk ) {

  auto table = fromFile( "zr-zrh.40t" );
  std::array< int32_t, 16 > iz = table.data().IZ();
  std::array< double, 16 > aw = table.data().AW();
  std::array< int64_t, 16 > nxs = table.data().NXS();
  std::array< int64_t, 32 > jxs = table.data().JXS();
  std::vector< double > xss = table.data().XSS();

  // IZ, AW, NXS, JXS, XSS arrays

  decltype(auto) iz_chunk = chunk.data().IZ();
  CHECK( iz.size() == iz_chunk.size() );
  for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {

    CHECK( iz[i] == iz_chunk[i] );
  }

  decltype(auto) aw_chunk = chunk.data().AW();
  CHECK( aw.size() == aw_chunk.size() );
  for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {

    CHECK_THAT( aw[i], WithinRel( aw_chunk[i] ) );
  }

  decltype(auto) nxs_chunk = chunk.data().NXS();
  CHECK( nxs.size() == nxs_chunk.size() );
  for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {

    CHECK( nxs[i] == nxs_chunk[i] );
  }

  decltype(auto) jxs_chunk = chunk.data().JXS();
  CHECK( jxs.size() == jxs_chunk.size() );
  for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {

    CHECK( jxs[i] == jxs_chunk[i] );
  }

  decltype(auto) xss_chunk = chunk.data().XSS();
  CHECK( xss.size() == xss_chunk.size() );
  for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // ThermalScatteringTable interface

  CHECK( "zr-zrh.40t" == chunk.ZAID() );
  CHECK_THAT( 2.5507e-8, WithinRel( chunk.temperature() ) );

  CHECK( 1091556 == chunk.length() );
  CHECK( 3 == chunk.IDPNI() );
  CHECK( 3 == chunk.inelasticScatteringMode() );
  CHECK( 21 == chunk.NIL() );
  CHECK( 21 == chunk.inelasticDimensioningParameter() );
  CHECK( 0 == chunk.NIEB() );
  CHECK( 0 == chunk.numberInelasticOutgoingEnergies() );
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
  CHECK( 91 == chunk.ITIE().numberIncidentEnergies() );

  CHECK( 91 == chunk.ITIE().energies().size() );
  CHECK_THAT( 1e-11, WithinRel( chunk.ITIE().energies().front() ) );
  CHECK_THAT( 9.5e-7, WithinRel( chunk.ITIE().energies().back() ) );

  CHECK( 91 == chunk.ITIE().crossSections().size() );
  CHECK_THAT( 2.619597, WithinRel( chunk.ITIE().crossSections().front() ) );
  CHECK_THAT( 5.3698962, WithinRel( chunk.ITIE().crossSections().back() ) );

  // ITXE block
  CHECK( false == chunk.ITXE().empty() );

  CHECK( 2 == chunk.ITXE().IFENG() );
  CHECK( 2 == chunk.ITXE().secondaryEnergyMode() );
  CHECK( 20 == chunk.ITXE().NC() );
  CHECK( 20 == chunk.ITXE().numberDiscreteCosines() );
  CHECK( 21 == chunk.ITXE().NIL() );
  CHECK( 21 == chunk.ITXE().inelasticDimensioningParameter() );
  CHECK( 91 == chunk.ITXE().NE() );
  CHECK( 91 == chunk.ITXE().numberIncidentEnergies() );

  // ITCE block
  CHECK( false == chunk.ITCE().has_value() );

  // ITCA block
  CHECK( false == chunk.ITCA().has_value() );

  // ITCEI block
  CHECK( false == chunk.ITCEI()->empty() );

  CHECK( 91 == chunk.ITCEI()->NE() );
  CHECK( 91 == chunk.ITCEI()->numberIncidentEnergies() );

  CHECK( 91 == chunk.ITCEI()->energies().size() );
  CHECK_THAT( 1e-11, WithinRel( chunk.ITCEI()->energies().front() ) );
  CHECK_THAT( 9.5e-7, WithinRel( chunk.ITCEI()->energies().back() ) );

  CHECK( 91 == chunk.ITCEI()->crossSections().size() );
  CHECK_THAT( 6.337617, WithinRel( chunk.ITCEI()->crossSections().front() ) );
  CHECK_THAT( 0.82849246, WithinRel( chunk.ITCEI()->crossSections().back() ) );

  // ITCAI block
  CHECK( false == chunk.ITCAI()->empty() );
  CHECK( 1820 == chunk.ITCAI()->length() );

  CHECK( 91 == chunk.ITCAI()->NE() );
  CHECK( 91 == chunk.ITCAI()->numberIncidentEnergies() );
  CHECK( 20 == chunk.ITCAI()->NC() );
  CHECK( 20 == chunk.ITCAI()->numberDiscreteCosines() );

  CHECK_THAT( -.9499973, WithinRel( chunk.ITCAI()->cosines( 1 )[0] ) );
  CHECK_THAT( .99335678, WithinRel( chunk.ITCAI()->cosines( 91 )[19] ) );
}

void verifyChunkAl( const ThermalScatteringTable& chunk ) {

  auto table = fromFile( "al-27.40t" );
  std::array< int32_t, 16 > iz = table.data().IZ();
  std::array< double, 16 > aw = table.data().AW();
  std::array< int64_t, 16 > nxs = table.data().NXS();
  std::array< int64_t, 32 > jxs = table.data().JXS();
  std::vector< double > xss = table.data().XSS();

  // IZ, AW, NXS, JXS, XSS arrays

  decltype(auto) iz_chunk = chunk.data().IZ();
  CHECK( iz.size() == iz_chunk.size() );
  for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {

    CHECK( iz[i] == iz_chunk[i] );
  }

  decltype(auto) aw_chunk = chunk.data().AW();
  CHECK( aw.size() == aw_chunk.size() );
  for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {

    CHECK_THAT( aw[i], WithinRel( aw_chunk[i] ) );
  }

  decltype(auto) nxs_chunk = chunk.data().NXS();
  CHECK( nxs.size() == nxs_chunk.size() );
  for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {

    CHECK( nxs[i] == nxs_chunk[i] );
  }

  decltype(auto) jxs_chunk = chunk.data().JXS();
  CHECK( jxs.size() == jxs_chunk.size() );
  for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {

    CHECK( jxs[i] == jxs_chunk[i] );
  }

  decltype(auto) xss_chunk = chunk.data().XSS();
  CHECK( xss.size() == xss_chunk.size() );
  for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // ThermalScatteringTable interface

  CHECK( "al-27.40t" == chunk.ZAID() );
  CHECK_THAT( 2.53e-8, WithinRel( chunk.temperature() ) );

  CHECK( 1066414 == chunk.length() );
  CHECK( 3 == chunk.IDPNI() );
  CHECK( 3 == chunk.inelasticScatteringMode() );
  CHECK( 21 == chunk.NIL() );
  CHECK( 21 == chunk.inelasticDimensioningParameter() );
  CHECK( 0 == chunk.NIEB() );
  CHECK( 0 == chunk.numberInelasticOutgoingEnergies() );
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
  CHECK( 100 == chunk.ITIE().numberIncidentEnergies() );

  CHECK( 100 == chunk.ITIE().energies().size() );
  CHECK_THAT( 1e-11, WithinRel( chunk.ITIE().energies().front() ) );
  CHECK_THAT( 2.18e-6, WithinRel( chunk.ITIE().energies().back() ) );

  CHECK( 100 == chunk.ITIE().crossSections().size() );
  CHECK_THAT( 1.677347, WithinRel( chunk.ITIE().crossSections().front() ) );
  CHECK_THAT( 1.31533352198, WithinRel( chunk.ITIE().crossSections().back() ) );

  // ITXE block
  CHECK( false == chunk.ITXE().empty() );

  CHECK( 2 == chunk.ITXE().IFENG() );
  CHECK( 2 == chunk.ITXE().secondaryEnergyMode() );
  CHECK( 20 == chunk.ITXE().NC() );
  CHECK( 20 == chunk.ITXE().numberDiscreteCosines() );
  CHECK( 21 == chunk.ITXE().NIL() );
  CHECK( 21 == chunk.ITXE().inelasticDimensioningParameter() );
  CHECK( 100 == chunk.ITXE().NE() );
  CHECK( 100 == chunk.ITXE().numberIncidentEnergies() );

  // ITCE block
  CHECK( false == chunk.ITCE()->empty() );

  CHECK( 119 == chunk.ITCE()->NE() );
  CHECK( 119 == chunk.ITCE()->numberIncidentEnergies() );

  CHECK( 119 == chunk.ITCE()->energies().size() );
  CHECK_THAT( 3.759019e-9, WithinRel( chunk.ITCE()->energies().front() ) );
  CHECK_THAT( 5.813947e-7, WithinRel( chunk.ITCE()->energies().back() ) );

  CHECK( 119 == chunk.ITCE()->crossSections().size() );
  CHECK_THAT( 5.10384187842E-09, WithinRel( chunk.ITCE()->crossSections().front() ) );
  CHECK_THAT( 7.15617224626E-08, WithinRel( chunk.ITCE()->crossSections().back() ) );

  // ITCA block
  CHECK( false == chunk.ITCA().has_value() );

  // ITCEI block
  CHECK( false == chunk.ITCEI().has_value() );

  // ITCAI block
  CHECK( false == chunk.ITCAI().has_value() );
}

void verifyChunkDLiD( const ThermalScatteringTable& chunk ) {

  auto table = fromFile( "d-lid.10t" );
  std::array< int32_t, 16 > iz = table.data().IZ();
  std::array< double, 16 > aw = table.data().AW();
  std::array< int64_t, 16 > nxs = table.data().NXS();
  std::array< int64_t, 32 > jxs = table.data().JXS();
  std::vector< double > xss = table.data().XSS();

  // IZ, AW, NXS, JXS, XSS arrays

  decltype(auto) iz_chunk = chunk.data().IZ();
  CHECK( iz.size() == iz_chunk.size() );
  for ( unsigned int i = 0; i < iz_chunk.size(); ++i ) {

    CHECK( iz[i] == iz_chunk[i] );
  }

  decltype(auto) aw_chunk = chunk.data().AW();
  CHECK( aw.size() == aw_chunk.size() );
  for ( unsigned int i = 0; i < aw_chunk.size(); ++i ) {

    CHECK_THAT( aw[i], WithinRel( aw_chunk[i] ) );
  }

  decltype(auto) nxs_chunk = chunk.data().NXS();
  CHECK( nxs.size() == nxs_chunk.size() );
  for ( unsigned int i = 0; i < nxs_chunk.size(); ++i ) {

    CHECK( nxs[i] == nxs_chunk[i] );
  }

  decltype(auto) jxs_chunk = chunk.data().JXS();
  CHECK( jxs.size() == jxs_chunk.size() );
  for ( unsigned int i = 0; i < jxs_chunk.size(); ++i ) {

    CHECK( jxs[i] == jxs_chunk[i] );
  }

  decltype(auto) xss_chunk = chunk.data().XSS();
  CHECK( xss.size() == xss_chunk.size() );
  for ( unsigned int i = 0; i < xss_chunk.size(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // ThermalScatteringTable interface

  CHECK( "d-lid.10t" == chunk.ZAID() );
  CHECK_THAT( 3.4469e-8, WithinRel( chunk.temperature() ) );

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
  CHECK( 117 == chunk.ITIE().numberIncidentEnergies() );

  CHECK( 117 == chunk.ITIE().energies().size() );
  CHECK_THAT( 1e-11, WithinRel( chunk.ITIE().energies().front() ) );
  CHECK_THAT( 9.85e-6, WithinRel( chunk.ITIE().energies().back() ) );

  CHECK( 117 == chunk.ITIE().crossSections().size() );
  CHECK_THAT( 14.55274, WithinRel( chunk.ITIE().crossSections().front() ) );
  CHECK_THAT( 1.68978156625, WithinRel( chunk.ITIE().crossSections().back() ) );

  // ITXE block
  CHECK( false == chunk.ITXE().empty() );

  CHECK( 1 == chunk.ITXE().IFENG() );
  CHECK( 1 == chunk.ITXE().secondaryEnergyMode() );
  CHECK( 20 == chunk.ITXE().NC() );
  CHECK( 20 == chunk.ITXE().numberDiscreteCosines() );
  CHECK( 19 == chunk.ITXE().NIL() );
  CHECK( 19 == chunk.ITXE().inelasticDimensioningParameter() );
  CHECK( 117 == chunk.ITXE().NE() );
  CHECK( 117 == chunk.ITXE().numberIncidentEnergies() );

  // ITCE block
  CHECK( false == chunk.ITCE()->empty() );

  CHECK( 72 == chunk.ITCE()->NE() );
  CHECK( 72 == chunk.ITCE()->numberIncidentEnergies() );

  CHECK( 72 == chunk.ITCE()->energies().size() );
  CHECK_THAT( 3.70672e-9, WithinRel( chunk.ITCE()->energies().front() ) );
  CHECK_THAT( 3.66965e-7, WithinRel( chunk.ITCE()->energies().back() ) );

  CHECK( 72 == chunk.ITCE()->crossSections().size() );
  CHECK_THAT( 3.75735379520E-09, WithinRel( chunk.ITCE()->crossSections().front() ) );
  CHECK_THAT( 8.39439776800E-08, WithinRel( chunk.ITCE()->crossSections().back() ) );

  // ITCA block
  CHECK( false == chunk.ITCA().has_value() );

  // ITCEI block
  CHECK( false == chunk.ITCEI()->empty() );

  CHECK( 117 == chunk.ITCEI()->NE() );
  CHECK( 117 == chunk.ITCEI()->numberIncidentEnergies() );

  CHECK( 117 == chunk.ITCEI()->energies().size() );
  CHECK_THAT( 1e-11, WithinRel( chunk.ITCEI()->energies().front() ) );
  CHECK_THAT( 9.85e-6, WithinRel( chunk.ITCEI()->energies().back() ) );

  CHECK( 117 == chunk.ITCEI()->crossSections().size() );
  CHECK_THAT( 1.026886, WithinRel( chunk.ITCEI()->crossSections().front() ) );
  CHECK_THAT( 2.48815555289E-03, WithinRel( chunk.ITCEI()->crossSections().back() ) );

  // ITCAI block
  CHECK( false == chunk.ITCAI()->empty() );

  CHECK( 117 == chunk.ITCAI()->NE() );
  CHECK( 117 == chunk.ITCAI()->numberIncidentEnergies() );
  CHECK( 20 == chunk.ITCAI()->NC() );
  CHECK( 20 == chunk.ITCAI()->numberDiscreteCosines() );

  CHECK_THAT( -9.49989880639E-01, WithinRel( chunk.ITCAI()->cosines( 1 )[0] ) );
  CHECK_THAT( 9.99876836853E-01, WithinRel( chunk.ITCAI()->cosines( 117 )[19] ) );
}
