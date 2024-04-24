// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/PhotoatomicTable.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::ACEtk;

void verifyChunkMcplib( const PhotoatomicTable& );
void verifyChunkMcplib03( const PhotoatomicTable& );
void verifyChunkEprdata12( const PhotoatomicTable& );
void verifyChunkEprdata14( const PhotoatomicTable& );

SCENARIO( "PhotoatomicTable" ){

  GIVEN( "valid data for a PhotoatomicTable - mcplib" ) {

    auto table = fromFile( "1000.01p" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a PhotoatomicTable from a table" ) {

      PhotoatomicTable chunk( std::move( table ) );

      THEN( "a PhotoatomicTable can be constructed and members can be "
            "tested" ) {

        verifyChunkMcplib( chunk );
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

    WHEN( "constructing a PhotoatomicTable from its components" ) {

      PhotoatomicTable base( std::move( table ) );

      PhotoatomicTable chunk( 1, base.header(),
                              { 1001, 1002, 1003 },
                              { 0.999167, 1.996800, 2.990140 },
                              base.ESZG(), base.JINC(),
                              base.JCOH(), base.LHNM(),
                              std::nullopt, std::nullopt,
                              std::nullopt, std::nullopt,
                              std::nullopt, std::nullopt,
                              std::nullopt, std::nullopt,
                              std::nullopt, {  },
                              std::nullopt, std::nullopt,
                              std::nullopt );

      THEN( "a PhotoatomicTable can be constructed and members can be "
            "tested" ) {

        verifyChunkMcplib( chunk );
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

  GIVEN( "valid data for a PhotoatomicTable - mcplib03" ) {

    auto table = fromFile( "3000.03p" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a PhotoatomicTable from a table" ) {

      PhotoatomicTable chunk( std::move( table ) );

      THEN( "a PhotoatomicTable can be constructed and members can be "
            "tested" ) {

        verifyChunkMcplib03( chunk );
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

    WHEN( "constructing a PhotoatomicTable from its components" ) {

      PhotoatomicTable base( std::move( table ) );

      PhotoatomicTable chunk( 3, base.header(),
                              {  },
                              {  },
                              base.ESZG(), base.JINC(),
                              base.JCOH(), base.LHNM(),
                              std::nullopt,
                              base.EPS(), base.SWD(),
                              std::nullopt, std::nullopt,
                              std::nullopt, std::nullopt,
                              std::nullopt, std::nullopt,
                              {  }, std::nullopt,
                              std::nullopt, std::nullopt );

      THEN( "a PhotoatomicTable can be constructed and members can be "
            "tested" ) {

        verifyChunkMcplib03( chunk );
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

  GIVEN( "valid data for a PhotoatomicTable - eprdata12" ) {

    auto table = fromFile( "1000.12p" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a PhotoatomicTable from a table" ) {

      PhotoatomicTable chunk( std::move( table ) );

      THEN( "a PhotoatomicTable can be constructed and members can be "
            "tested" ) {

        verifyChunkEprdata12( chunk );
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

    WHEN( "constructing a PhotoatomicTable from its components" ) {

      PhotoatomicTable base( std::move( table ) );

      std::vector< electron::EION > eion = std::vector< electron::EION >{};
      for ( unsigned int index = 1; index <= base.NSSH(); ++index ) {

        eion.push_back( base.EION( index ) );
      }

      PhotoatomicTable chunk( 1, base.header(),
                              {  },
                              {  },
                              base.ESZG(), base.JINC(),
                              base.JCOH(), base.LHNM(),
                              std::nullopt,
                              base.EPS(), base.SWD(),
                              base.SUBSH(), base.SPHEL(),
                              base.XPROB(), base.ESZE(),
                              base.EXCIT(), base.ELAS(),
                              std::move( eion ),
                              base.BREME(), base.BREML(),
                              std::nullopt );

      THEN( "a PhotoatomicTable can be constructed and members can be "
            "tested" ) {

        verifyChunkEprdata12( chunk );
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

  GIVEN( "valid data for a PhotoatomicTable - eprdata14" ) {

    auto table = fromFile( "6000.14p" );
    std::array< int32_t, 16 > iz = table.data().IZ();
    std::array< double, 16 > aw = table.data().AW();
    std::array< int64_t, 16 > nxs = table.data().NXS();
    std::array< int64_t, 32 > jxs = table.data().JXS();
    std::vector< double > xss = table.data().XSS();

    WHEN( "constructing a PhotoatomicTable from a table" ) {

      PhotoatomicTable chunk( std::move( table ) );

      THEN( "a PhotoatomicTable can be constructed and members can be "
            "tested" ) {

        verifyChunkEprdata14( chunk );
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

    WHEN( "constructing a PhotoatomicTable from its components" ) {

      PhotoatomicTable base( std::move( table ) );

      std::vector< electron::EION > eion = std::vector< electron::EION >{};
      for ( unsigned int index = 1; index <= base.NSSH(); ++index ) {

        eion.push_back( base.EION( index ) );
      }

      PhotoatomicTable chunk( 6, base.header(),
                              {  },
                              {  },
                              base.ESZG(), base.JINC(),
                              base.JCOH(), base.LHNM(),
                              std::nullopt,
                              base.EPS(), base.SWD(),
                              base.SUBSH(), base.SPHEL(),
                              base.XPROB(), base.ESZE(),
                              base.EXCIT(), base.ELAS(),
                              std::move( eion ),
                              base.BREME(), base.BREML(),
                              base.SELAS() );

      THEN( "a PhotoatomicTable can be constructed and members can be "
            "tested" ) {

        verifyChunkEprdata14( chunk );
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
  }
} // SCENARIO

void verifyChunkMcplib( const PhotoatomicTable& chunk ) {

  CHECK( "1000.01p" == chunk.ZAID() );
  CHECK_THAT( 0., WithinRel( chunk.temperature() ) );

  CHECK( 389 == chunk.length() );
  CHECK( 0 == chunk.S() );
  CHECK( 0 == chunk.isomericState() );
  CHECK( 1 == chunk.Z() );
  CHECK( 1 == chunk.atomNumber() );
  CHECK( 0 == chunk.A() );
  CHECK( 0 == chunk.massNumber() );
  CHECK( 43 == chunk.NES() );
  CHECK( 43 == chunk.numberEnergyPoints() );
  CHECK( 0 == chunk.NFLO() );
  CHECK( 0 == chunk.numberFluorescenceEdges() );
  CHECK( 0 == chunk.NSH() );
  CHECK( 0 == chunk.numberElectronShells() );

  // this is an old format file so no EPR data blocks are presents
  CHECK( 0 == chunk.NEPR() );
  CHECK( 0 == chunk.electronPhotonRelaxationFormat() );
  CHECK( 0 == chunk.NSSH() );
  CHECK( 0 == chunk.numberElectronSubshells() );
  CHECK( 0 == chunk.NE() );
  CHECK( 0 == chunk.numberElectronEnergyPoints() );
  CHECK( 0 == chunk.NXL() );
  CHECK( 0 == chunk.numberElectronExcitationEnergyPoints() );
  CHECK( 0 == chunk.NA() );
  CHECK( 0 == chunk.numberElectronElasticEnergyPoints() );
  CHECK( 0 == chunk.NB() );
  CHECK( 0 == chunk.numberPhotonBremsstrahlungEnergyPoints() );
  CHECK( 0 == chunk.NBL() );
  CHECK( 0 == chunk.numberElectronBremsstrahlungEnergyPoints() );
  CHECK( 0 == chunk.NINC() );
  CHECK( 0 == chunk.numberIncoherentMomentumValues() );
  CHECK( 0 == chunk.NCOH() );
  CHECK( 0 == chunk.numberCoherentMomentumValues() );

  // ESZG block
  CHECK( false == chunk.ESZG().empty() );

  CHECK( 43 == chunk.ESZG().NES() );
  CHECK( 43 == chunk.ESZG().numberEnergyPoints() );

  CHECK( 43 == chunk.ESZG().energies().size() );
  CHECK( 43 == chunk.ESZG().incoherent().size() );
  CHECK( 43 == chunk.ESZG().coherent().size() );
  CHECK( 43 == chunk.ESZG().photoelectric().size() );
  CHECK( 43 == chunk.ESZG().pairproduction().size() );

  CHECK_THAT( -6.907755278982E+00, WithinRel( chunk.ESZG().energies().front() ) );
  CHECK_THAT(  4.605170185988E+00, WithinRel( chunk.ESZG().energies().back() ) );
  CHECK_THAT( -2.474115088710E+00, WithinRel( chunk.ESZG().incoherent().front() ) );
  CHECK_THAT( -4.794460770140E+00, WithinRel( chunk.ESZG().incoherent().back() ) );
  CHECK_THAT( -5.438809818403E-01, WithinRel( chunk.ESZG().coherent().front() ) );
  CHECK_THAT( -2.149558177385E+01, WithinRel( chunk.ESZG().coherent().back() ) );
  CHECK_THAT(  2.449279472145E+00, WithinRel( chunk.ESZG().photoelectric().front() ) );
  CHECK_THAT( -2.622629761934E+01, WithinRel( chunk.ESZG().photoelectric().back() ) );
  CHECK_THAT(  0.000000000000E+00, WithinRel( chunk.ESZG().pairproduction().front() ) );
  CHECK_THAT( -4.455371820900E+00, WithinRel( chunk.ESZG().pairproduction().back() ) );

  // JINC block
  CHECK( false == chunk.JINC().empty() );

  CHECK( 21 == chunk.JINC().NM() );
  CHECK( 21 == chunk.JINC().numberValues() );

  CHECK( 21 == chunk.JINC().momentum().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.JINC().momentum().front() ) );
  CHECK_THAT( 8.  , WithinRel( chunk.JINC().momentum().back() ) );

  CHECK( 21 == chunk.JINC().values().size() );
  CHECK_THAT( 0, WithinRel( chunk.JINC().values().front() ) );
  CHECK_THAT( 1, WithinRel( chunk.JINC().values().back() ) );

  // JCOH block
  CHECK( false == chunk.JCOH().empty() );

  CHECK( 55 == chunk.JCOH().NM() );
  CHECK( 55 == chunk.JCOH().numberValues() );

  CHECK( 55 == chunk.JCOH().momentum().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.JCOH().momentum().front() ) );
  CHECK_THAT( 6.  , WithinRel( chunk.JCOH().momentum().back() ) );

  CHECK( 55 == chunk.JCOH().integratedFormFactors().size() );
  CHECK_THAT( 0., WithinRel( chunk.JCOH().integratedFormFactors().front() ) );
  CHECK_THAT( 3.058316405266E-02, WithinRel( chunk.JCOH().integratedFormFactors().back() ) );

  CHECK( 55 == chunk.JCOH().formFactors().size() );
  CHECK_THAT( 1., WithinRel( chunk.JCOH().formFactors().front() ) );
  CHECK_THAT( 6.282390000000E-06, WithinRel( chunk.JCOH().formFactors().back() ) );

  // JFLO block
  CHECK( false == chunk.JFLO().has_value() );

  // LHNM block
  CHECK( false == chunk.LHNM().empty() );

  CHECK( 43 == chunk.LHNM().NES() );
  CHECK( 43 == chunk.LHNM().numberEnergyPoints() );
  CHECK( 43 == chunk.LHNM().heating().size() );

  CHECK_THAT( 9.457315870945E-04, WithinRel( chunk.LHNM().heating().front() ) );
  CHECK_THAT( 9.086036433693E+01, WithinRel( chunk.LHNM().heating().back() ) );

  // EPS block
  CHECK( false == chunk.EPS().has_value() );

  // SWD block
  CHECK( false == chunk.SWD().has_value() );

  // SUBSH block - not an EPR data file
  CHECK( false == chunk.SUBSH().has_value() );

  // SPHEL block - not an EPR data file
  CHECK( false == chunk.SPHEL().has_value() );

  // XPROB block - not EPR data file
  CHECK( false == chunk.XPROB().has_value() );

  // ESZE block - not EPR data file
  CHECK( false == chunk.ESZE().has_value() );

  // EXCIT block - not EPR data file
  CHECK( false == chunk.EXCIT().has_value() );

  // ELAS block - not EPR data file
  CHECK( false == chunk.ELAS().has_value() );

  // other blocks go here

  // BREME block - not EPR data file
  CHECK( false == chunk.BREME().has_value() );

  // BREML block - not EPR data file
  CHECK( false == chunk.BREML().has_value() );

  // SELAS block - not EPR data file
  CHECK( false == chunk.SELAS().has_value() );
}

void verifyChunkMcplib03( const PhotoatomicTable& chunk ) {

  CHECK( "3000.03p" == chunk.ZAID() );
  CHECK_THAT( 0., WithinRel( chunk.temperature() ) );

  CHECK( 821 == chunk.length() );
  CHECK( 0 == chunk.S() );
  CHECK( 0 == chunk.isomericState() );
  CHECK( 3 == chunk.Z() );
  CHECK( 3 == chunk.atomNumber() );
  CHECK( 0 == chunk.A() );
  CHECK( 0 == chunk.massNumber() );
  CHECK( 82 == chunk.NES() );
  CHECK( 82 == chunk.numberEnergyPoints() );
  CHECK( 0 == chunk.NFLO() );
  CHECK( 0 == chunk.numberFluorescenceEdges() );
  CHECK( 2 == chunk.NSH() );
  CHECK( 2 == chunk.numberElectronShells() );

  // this is an old format file so no EPR data blocks are presents
  CHECK( 0 == chunk.NEPR() );
  CHECK( 0 == chunk.electronPhotonRelaxationFormat() );
  CHECK( 0 == chunk.NSSH() );
  CHECK( 0 == chunk.numberElectronSubshells() );
  CHECK( 0 == chunk.NE() );
  CHECK( 0 == chunk.numberElectronEnergyPoints() );
  CHECK( 0 == chunk.NXL() );
  CHECK( 0 == chunk.numberElectronExcitationEnergyPoints() );
  CHECK( 0 == chunk.NA() );
  CHECK( 0 == chunk.numberElectronElasticEnergyPoints() );
  CHECK( 0 == chunk.NB() );
  CHECK( 0 == chunk.numberPhotonBremsstrahlungEnergyPoints() );
  CHECK( 0 == chunk.NBL() );
  CHECK( 0 == chunk.numberElectronBremsstrahlungEnergyPoints() );
  CHECK( 0 == chunk.NINC() );
  CHECK( 0 == chunk.numberIncoherentMomentumValues() );
  CHECK( 0 == chunk.NCOH() );
  CHECK( 0 == chunk.numberCoherentMomentumValues() );

  // ESZG block
  CHECK( false == chunk.ESZG().empty() );

  CHECK( 82 == chunk.ESZG().NES() );
  CHECK( 82 == chunk.ESZG().numberEnergyPoints() );

  CHECK( 82 == chunk.ESZG().energies().size() );
  CHECK( 82 == chunk.ESZG().incoherent().size() );
  CHECK( 82 == chunk.ESZG().coherent().size() );
  CHECK( 82 == chunk.ESZG().photoelectric().size() );
  CHECK( 82 == chunk.ESZG().pairproduction().size() );

  CHECK_THAT( -6.907755278982E+00, WithinRel( chunk.ESZG().energies().front() ) );
  CHECK_THAT(  1.151292546497E+01, WithinRel( chunk.ESZG().energies().back() ) );
  CHECK_THAT( -1.036037569528E+00, WithinRel( chunk.ESZG().incoherent().front() ) );
  CHECK_THAT( -9.880667912376E+00, WithinRel( chunk.ESZG().incoherent().back() ) );
  CHECK_THAT(  1.556749961755E+00, WithinRel( chunk.ESZG().coherent().front() ) );
  CHECK_THAT( -3.192069466597E+01, WithinRel( chunk.ESZG().coherent().back() ) );
  CHECK_THAT(  7.753623546560E+00, WithinRel( chunk.ESZG().photoelectric().front() ) );
  CHECK_THAT( -2.663665884863E+01, WithinRel( chunk.ESZG().photoelectric().back() ) );
  CHECK_THAT(                   0, WithinRel( chunk.ESZG().pairproduction().front() ) );
  CHECK_THAT( -2.222019445154E+00, WithinRel( chunk.ESZG().pairproduction().back() ) );

  // JINC block
  CHECK( false == chunk.JINC().empty() );

  CHECK( 21 == chunk.JINC().NM() );
  CHECK( 21 == chunk.JINC().numberValues() );

  CHECK( 21 == chunk.JINC().momentum().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.JINC().momentum().front() ) );
  CHECK_THAT( 8.  , WithinRel( chunk.JINC().momentum().back() ) );

  CHECK( 21 == chunk.JINC().values().size() );
  CHECK_THAT( 0, WithinRel( chunk.JINC().values().front() ) );
  CHECK_THAT( 3, WithinRel( chunk.JINC().values().back() ) );

  // JCOH block
  CHECK( false == chunk.JCOH().empty() );

  CHECK( 55 == chunk.JCOH().NM() );
  CHECK( 55 == chunk.JCOH().numberValues() );

  CHECK( 55 == chunk.JCOH().momentum().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.JCOH().momentum().front() ) );
  CHECK_THAT( 6.  , WithinRel( chunk.JCOH().momentum().back() ) );

  CHECK( 55 == chunk.JCOH().integratedFormFactors().size() );
  CHECK_THAT( 0., WithinRel( chunk.JCOH().integratedFormFactors().front() ) );
  CHECK_THAT( 9.972763100947E-02, WithinRel( chunk.JCOH().integratedFormFactors().back() ) );

  CHECK( 55 == chunk.JCOH().formFactors().size() );
  CHECK_THAT( 3., WithinRel( chunk.JCOH().formFactors().front() ) );
  CHECK_THAT( 7.806310000000E-04, WithinRel( chunk.JCOH().formFactors().back() ) );

  // JFLO block
  CHECK( false == chunk.JFLO().has_value() );

  // LHNM block
  CHECK( false == chunk.LHNM().empty() );

  CHECK( 82 == chunk.LHNM().NES() );
  CHECK( 82 == chunk.LHNM().numberEnergyPoints() );
  CHECK( 82 == chunk.LHNM().heating().size() );

  CHECK_THAT( 9.978170710722E-04, WithinRel( chunk.LHNM().heating().front() ) );
  CHECK_THAT( 9.999428234605E+04, WithinRel( chunk.LHNM().heating().back() ) );

  // EPS block
  CHECK( false == chunk.EPS()->empty() );

  CHECK( 2 == chunk.EPS()->NSH() );
  CHECK( 2 == chunk.EPS()->numberElectronShells() );

  CHECK_THAT( 2, WithinRel( chunk.EPS()->numberElectrons()[0] ) );
  CHECK_THAT( 1, WithinRel( chunk.EPS()->numberElectrons()[1] ) );
  CHECK_THAT( 5.480000000000e-05, WithinRel( chunk.EPS()->bindingEnergies()[0] ) );
  CHECK_THAT( 1.000000000000e-06, WithinRel( chunk.EPS()->bindingEnergies()[1] ) );
  CHECK_THAT( 6.666666666667e-01, WithinRel( chunk.EPS()->interactionProbabilities()[0] ) );
  CHECK_THAT( 3.333333333333e-01, WithinRel( chunk.EPS()->interactionProbabilities()[1] ) );

  CHECK( 2 == chunk.EPS()->numberElectronsPerShell( 1 ) );
  CHECK( 1 == chunk.EPS()->numberElectronsPerShell( 2 ) );
  CHECK_THAT( 5.480000000000e-05, WithinRel( chunk.EPS()->bindingEnergy( 1 ) ) );
  CHECK_THAT( 1.000000000000e-06, WithinRel( chunk.EPS()->bindingEnergy( 2 ) ) );
  CHECK_THAT( 6.666666666667e-01, WithinRel( chunk.EPS()->interactionProbability( 1 ) ) );
  CHECK_THAT( 3.333333333333e-01, WithinRel( chunk.EPS()->interactionProbability( 2 ) ) );

  // SWD block
  CHECK( false == chunk.SWD()->empty() );

  CHECK( 2 == chunk.SWD()->NSH() );

  CHECK( 1 == chunk.SWD()->LSWD( 1 ) );
  CHECK( 96 == chunk.SWD()->LSWD( 2 ) );

  auto profile = chunk.SWD()->comptonProfile(1);
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK_THAT( 0., WithinRel( profile.momentum().front() ) );
  CHECK_THAT( 100., WithinRel( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK_THAT( 6.527863344596e-01, WithinRel( profile.pdf().front() ) );
  CHECK_THAT( 3.571475386101e-10, WithinRel( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK_THAT( 0., WithinRel( profile.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( profile.cdf().back() ) );

  profile = chunk.SWD()->comptonProfile(2);
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK_THAT( 0., WithinRel( profile.momentum().front() ) );
  CHECK_THAT( 100., WithinRel( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK_THAT( 3.848272047027e+00, WithinRel( profile.pdf().front() ) );
  CHECK_THAT( 8.728039694288e-12, WithinRel( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK_THAT( 0., WithinRel( profile.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( profile.cdf().back() ) );

  // SUBSH block - not an EPR data file
  CHECK( false == chunk.SUBSH().has_value() );

  // SPHEL block - not an EPR data file
  CHECK( false == chunk.SPHEL().has_value() );

  // XPROB block - not EPR data file
  CHECK( false == chunk.XPROB().has_value() );

  // ESZE block - not EPR data file
  CHECK( false == chunk.ESZE().has_value() );

  // EXCIT block - not EPR data file
  CHECK( false == chunk.EXCIT().has_value() );

  // ELAS block - not EPR data file
  CHECK( false == chunk.ELAS().has_value() );

  // other blocks go here

  // BREME block - not EPR data file
  CHECK( false == chunk.BREME().has_value() );

  // BREML block - not EPR data file
  CHECK( false == chunk.BREML().has_value() );

  // SELAS block - not EPR data file
  CHECK( false == chunk.SELAS().has_value() );
}

void verifyChunkEprdata12( const PhotoatomicTable& chunk ) {

  CHECK( "1000.12p" == chunk.ZAID() );
  CHECK_THAT( 0., WithinRel( chunk.temperature() ) );

  CHECK( 12025 == chunk.length() );
  CHECK( 0 == chunk.S() );
  CHECK( 0 == chunk.isomericState() );
  CHECK( 1 == chunk.Z() );
  CHECK( 1 == chunk.atomNumber() );
  CHECK( 0 == chunk.A() );
  CHECK( 0 == chunk.massNumber() );
  CHECK( 647 == chunk.NES() );
  CHECK( 647 == chunk.numberEnergyPoints() );
  CHECK( 0 == chunk.NFLO() );
  CHECK( 0 == chunk.numberFluorescenceEdges() );
  CHECK( 1 == chunk.NSH() );
  CHECK( 1 == chunk.numberElectronShells() );

  // this is an EPR data file
  CHECK( 1 == chunk.NEPR() );
  CHECK( 1 == chunk.electronPhotonRelaxationFormat() );
  CHECK( 1 == chunk.NSSH() );
  CHECK( 1 == chunk.numberElectronSubshells() );
  CHECK( 342 == chunk.NE() );
  CHECK( 342 == chunk.numberElectronEnergyPoints() );
  CHECK( 170 == chunk.NXL() );
  CHECK( 170 == chunk.numberElectronExcitationEnergyPoints() );
  CHECK( 16 == chunk.NA() );
  CHECK( 16 == chunk.numberElectronElasticEnergyPoints() );
  CHECK( 10 == chunk.NB() );
  CHECK( 10 == chunk.numberPhotonBremsstrahlungEnergyPoints() );
  CHECK( 82 == chunk.NBL() );
  CHECK( 82 == chunk.numberElectronBremsstrahlungEnergyPoints() );
  CHECK( 0 == chunk.NINC() );
  CHECK( 0 == chunk.numberIncoherentMomentumValues() );
  CHECK( 0 == chunk.NCOH() );
  CHECK( 0 == chunk.numberCoherentMomentumValues() );

  // ESZG block
  CHECK( false == chunk.ESZG().empty() );

  CHECK( 647 == chunk.ESZG().NES() );
  CHECK( 647 == chunk.ESZG().numberEnergyPoints() );

  CHECK( 647 == chunk.ESZG().energies().size() );
  CHECK( 647 == chunk.ESZG().incoherent().size() );
  CHECK( 647 == chunk.ESZG().coherent().size() );
  CHECK( 647 == chunk.ESZG().photoelectric().size() );
  CHECK( 647 == chunk.ESZG().pairproduction().size() );

  CHECK_THAT( -1.381551055796E+01, WithinRel( chunk.ESZG().energies().front() ) );
  CHECK_THAT(  1.151292546497E+01, WithinRel( chunk.ESZG().energies().back() ) );
  CHECK_THAT( -1.616285246005E+01, WithinRel( chunk.ESZG().incoherent().front() ) );
  CHECK_THAT( -1.097982967256E+01, WithinRel( chunk.ESZG().incoherent().back() ) );
  CHECK_THAT( -1.152423386458E+01, WithinRel( chunk.ESZG().coherent().front() ) );
  CHECK_THAT( -3.530963433758E+01, WithinRel( chunk.ESZG().coherent().back() ) );
  CHECK_THAT(                   0, WithinRel( chunk.ESZG().photoelectric().front() ) );
  CHECK_THAT( -3.249289163676E+01, WithinRel( chunk.ESZG().photoelectric().back() ) );
  CHECK_THAT(                   0, WithinRel( chunk.ESZG().pairproduction().front() ) );
  CHECK_THAT( -3.877573270699E+00, WithinRel( chunk.ESZG().pairproduction().back() ) );

  // JINC block
  CHECK( false == chunk.JINC().empty() );

  CHECK( 94 == chunk.JINC().NM() );
  CHECK( 94 == chunk.JINC().numberValues() );

  CHECK( 94 == chunk.JINC().momentum().size() );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.JINC().momentum().front() ) );
  CHECK_THAT( 1.000000000000E+09, WithinRel( chunk.JINC().momentum().back() ) );

  CHECK( 94 == chunk.JINC().values().size() );
  CHECK_THAT( 0, WithinRel( chunk.JINC().values().front() ) );
  CHECK_THAT( 1, WithinRel( chunk.JINC().values().back() ) );

  // JCOH block
  CHECK( false == chunk.JCOH().empty() );

  CHECK( 90 == chunk.JCOH().NM() );
  CHECK( 90 == chunk.JCOH().numberValues() );

  CHECK( 90 == chunk.JCOH().momentum().size() );
  CHECK_THAT( 0.                , WithinRel( chunk.JCOH().momentum().front() ) );
  CHECK_THAT( 1.000000000000E+09, WithinRel( chunk.JCOH().momentum().back() ) );

  CHECK( 90 == chunk.JCOH().integratedFormFactors().size() );
  CHECK_THAT( 0.                , WithinRel( chunk.JCOH().integratedFormFactors().front() ) );
  CHECK_THAT( 3.012861887900E-02, WithinRel( chunk.JCOH().integratedFormFactors().back() ) );

  CHECK( 90 == chunk.JCOH().formFactors().size() );
  CHECK_THAT( 1.                , WithinRel( chunk.JCOH().formFactors().front() ) );
  CHECK_THAT( 8.182900000000E-39, WithinRel( chunk.JCOH().formFactors().back() ) );

  // JFLO block
  CHECK( false == chunk.JFLO().has_value() );

  // LHNM block
  CHECK( false == chunk.LHNM().empty() );

  CHECK( 647 == chunk.LHNM().NES() );
  CHECK( 647 == chunk.LHNM().numberEnergyPoints() );
  CHECK( 647 == chunk.LHNM().heating().size() );

  CHECK_THAT( 8.714616354250E-07, WithinRel( chunk.LHNM().heating().front() ) );
  CHECK_THAT( 9.999084183050E+04, WithinRel( chunk.LHNM().heating().back() ) );

  // EPS block
  CHECK( false == chunk.EPS()->empty() );

  CHECK( 1 == chunk.EPS()->NSH() );
  CHECK( 1 == chunk.EPS()->numberElectronShells() );

  CHECK( 1 == chunk.EPS()->numberElectrons()[0] );
  CHECK_THAT( 1.400000000000e-05, WithinRel( chunk.EPS()->bindingEnergies()[0] ) );
  CHECK_THAT( 1.000000000000e+00, WithinRel( chunk.EPS()->interactionProbabilities()[0] ) );

  CHECK( 1 == chunk.EPS()->numberElectronsPerShell( 1 ) );
  CHECK_THAT( 1.400000000000e-05, WithinRel( chunk.EPS()->bindingEnergy( 1 ) ) );
  CHECK_THAT( 1.000000000000e+00, WithinRel( chunk.EPS()->interactionProbability( 1 ) ) );

  // SWD block
  CHECK( false == chunk.SWD()->empty() );

  CHECK( 1 == chunk.SWD()->NSH() );

  CHECK( 1 == chunk.SWD()->LSWD( 1 ) );

  auto profile = chunk.SWD()->comptonProfile(1);
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK_THAT( 0., WithinRel( profile.momentum().front() ) );
  CHECK_THAT( 100., WithinRel( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK_THAT( 1.690581458877E+00, WithinRel( profile.pdf().front() ) );
  CHECK_THAT( 5.177281263934E-11, WithinRel( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK_THAT( 0., WithinRel( profile.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( profile.cdf().back() ) );

  // SUBSH block - EPR data file
  CHECK( true == chunk.SUBSH().has_value() );

  CHECK( 1 == chunk.SUBSH()->NSSH() );
  CHECK( 1 == chunk.SUBSH()->numberElectronSubshells() );

  CHECK( 1 == chunk.SUBSH()->ID()[0] );
  CHECK( 1 == chunk.SUBSH()->designators()[0] );

  CHECK( 1 == chunk.SUBSH()->EP()[0] );
  CHECK( 1 == chunk.SUBSH()->populations()[0] );

  CHECK_THAT( 1.361E-05, WithinRel( chunk.SUBSH()->BE()[0] ) );
  CHECK_THAT( 1.361E-05, WithinRel( chunk.SUBSH()->bindingEnergies()[0] ) );

  CHECK_THAT( 1., WithinRel( chunk.SUBSH()->CV()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.SUBSH()->vacancyProbabilities()[0] ) );

  CHECK( 0 == chunk.SUBSH()->NT()[0] );
  CHECK( 0 == chunk.SUBSH()->numberTransitions()[0] );

  CHECK( 1 == chunk.SUBSH()->designator( 1 ) );

  CHECK( 1 == chunk.SUBSH()->population( 1 ) );

  CHECK_THAT( 1.361E-05, WithinRel( chunk.SUBSH()->bindingEnergy( 1 ) ) );

  CHECK_THAT( 1., WithinRel( chunk.SUBSH()->vacancyProbability( 1 ) ) );

  CHECK( 0 == chunk.SUBSH()->numberTransitions( 1 ) );

  // SPHEL block - EPR data file
  CHECK( true == chunk.SPHEL().has_value() );

  CHECK( 647 == chunk.SPHEL()->NES() );
  CHECK( 647 == chunk.SPHEL()->numberEnergyPoints() );
  CHECK( 1 == chunk.SPHEL()->NSSH() );
  CHECK( 1 == chunk.SPHEL()->numberElectronSubshells() );

  CHECK( 647 == chunk.SPHEL()->photoelectric(1).size() );

  CHECK_THAT(  0.000000000000E+00, WithinRel( chunk.SPHEL()->photoelectric(1).front() ) );
  CHECK_THAT( -3.249289163676E+01, WithinRel( chunk.SPHEL()->photoelectric(1).back() ) );

  // XPROB block - EPR data file
  CHECK( true == chunk.XPROB().has_value() );

  CHECK( 1 == chunk.XPROB()->NSSH() );
  CHECK( 1 == chunk.XPROB()->numberElectronSubshells() );
  CHECK( 1 == chunk.XPROB()->data().size() );

  CHECK(  1 == chunk.XPROB()->LTRAN(1) );
  CHECK(  1 == chunk.XPROB()->transitionDataLocator(1) );

  CHECK( true == chunk.XPROB()->transitionData(1).empty() );

  // ESZE block - EPR data file
  CHECK( true == chunk.ESZE().has_value() );

  CHECK( 342 == chunk.ESZE()->NE() );
  CHECK( 342 == chunk.ESZE()->numberEnergyPoints() );
  CHECK( 1 == chunk.ESZE()->NSSH() );
  CHECK( 1 == chunk.ESZE()->numberElectronSubshells() );

  CHECK( 342 == chunk.ESZE()->energies().size() );
  CHECK( 342 == chunk.ESZE()->total().size() );
  CHECK( 342 == chunk.ESZE()->elastic().size() );
  CHECK( 342 == chunk.ESZE()->bremsstrahlung().size() );
  CHECK( 342 == chunk.ESZE()->excitation().size() );
  CHECK( 342 == chunk.ESZE()->totalElectroionisation().size() );
  CHECK( 342 == chunk.ESZE()->electroionisation(1).size() );

  CHECK_THAT( 1.000000000000E-05, WithinRel( chunk.ESZE()->energies().front() ) );
  CHECK_THAT( 1.000000000000E+05, WithinRel( chunk.ESZE()->energies().back() ) );
  CHECK_THAT( 2.748960297832E+08, WithinRel( chunk.ESZE()->total().front() ) );
  CHECK_THAT( 1.643349906341E+05, WithinRel( chunk.ESZE()->total().back() ) );
  CHECK_THAT( 2.748960000000E+08, WithinRel( chunk.ESZE()->elastic().front() ) );
  CHECK_THAT( 1.311760000000E-05, WithinRel( chunk.ESZE()->elastic().back() ) );
  CHECK_THAT( 2.978320000000E+01, WithinRel( chunk.ESZE()->bremsstrahlung().front() ) );
  CHECK_THAT( 9.906210000000E-01, WithinRel( chunk.ESZE()->bremsstrahlung().back() ) );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.ESZE()->excitation().front() ) );
  CHECK_THAT( 8.144160000000E+04, WithinRel( chunk.ESZE()->excitation().back() ) );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.ESZE()->totalElectroionisation().front() ) );
  CHECK_THAT( 8.289240000000E+04, WithinRel( chunk.ESZE()->totalElectroionisation().back() ) );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.ESZE()->electroionisation(1).front() ) );
  CHECK_THAT( 8.289240000000E+04, WithinRel( chunk.ESZE()->electroionisation(1).back() ) );

  // EXCIT block - EPR data file
  CHECK( true == chunk.EXCIT().has_value() );

  CHECK( 170 == chunk.EXCIT()->NXL() );
  CHECK( 170 == chunk.EXCIT()->numberEnergyPoints() );

  CHECK( 170 == chunk.EXCIT()->energies().size() );
  CHECK( 170 == chunk.EXCIT()->excitationEnergyLoss().size() );

  CHECK_THAT( 1.361000000000E-05, WithinRel( chunk.EXCIT()->energies().front() ) );
  CHECK_THAT( 1.000000000000E+05, WithinRel( chunk.EXCIT()->energies().back() ) );

  CHECK_THAT( 1.351000000000E-05, WithinRel( chunk.EXCIT()->excitationEnergyLoss().front() ) );
  CHECK_THAT( 2.107770000000E-05, WithinRel( chunk.EXCIT()->excitationEnergyLoss().back() ) );

  // ELAS block - EPR data file
  CHECK( true == chunk.ELAS().has_value() );

  CHECK( 16 == chunk.ELAS()->NA() );
  CHECK( 16 == chunk.ELAS()->numberEnergyPoints() );
  CHECK( 16 == chunk.ELAS()->energies().size() );
  CHECK( 16 == chunk.ELAS()->distributions().size() );

  auto distribution = chunk.ELAS()->distribution(1);
  CHECK( 1.000000000000E-05 == distribution.energy() );
  CHECK( 3 == distribution.numberCosines() );

  CHECK_THAT( -1., WithinRel( distribution.cosines()[0] ) );
  CHECK_THAT( 9.9999900000E-01, WithinRel( distribution.cosines()[1] ) );
  CHECK_THAT(  1., WithinRel( distribution.cosines()[2] ) );

  CHECK_THAT( 0., WithinRel( distribution.cdf()[0] ) );
  CHECK_THAT( 9.9999950000E-01, WithinRel( distribution.cdf()[1] ) );
  CHECK_THAT( 1., WithinRel( distribution.cdf()[2] ) );

  distribution = chunk.ELAS()->distribution(16);
  CHECK( 1e+5 == distribution.energy() );
  CHECK( 91 == distribution.numberCosines() );

  // EION block - EPR data file
  CHECK( false == chunk.EION( 1 ).empty() );

  CHECK( 8 == chunk.EION( 1 ).NB() );
  CHECK( 8 == chunk.EION( 1 ).numberEnergyPoints() );
  CHECK( 8 == chunk.EION( 1 ).energies().size() );
  CHECK( 8 == chunk.EION( 1 ).distributions().size() );

  auto eiondistribution = chunk.EION( 1 ).distribution(1);
  CHECK_THAT( 1.361000000000E-05, WithinRel( eiondistribution.energy() ) );
  CHECK( 2 == eiondistribution.numberOutgoingEnergies() );

  eiondistribution = chunk.EION( 1 ).distribution(3);
  CHECK_THAT( 1.000000E-04, WithinRel( eiondistribution.energy() ) );
  CHECK( 14 == eiondistribution.numberOutgoingEnergies() );

  CHECK_THAT( 1.000000000000E-07, WithinRel( eiondistribution.outgoingEnergies()[0] ) );
  CHECK_THAT( 6.309570000000E-07, WithinRel( eiondistribution.outgoingEnergies()[1] ) );
  CHECK_THAT( 1.122020000000E-06, WithinRel( eiondistribution.outgoingEnergies()[2] ) );
  CHECK_THAT( 1.995260000000E-06, WithinRel( eiondistribution.outgoingEnergies()[3] ) );
  CHECK_THAT( 3.162280000000E-06, WithinRel( eiondistribution.outgoingEnergies()[4] ) );
  CHECK_THAT( 5.011870000000E-06, WithinRel( eiondistribution.outgoingEnergies()[5] ) );
  CHECK_THAT( 6.309580000000E-06, WithinRel( eiondistribution.outgoingEnergies()[6] ) );
  CHECK_THAT( 8.912530000000E-06, WithinRel( eiondistribution.outgoingEnergies()[7] ) );
  CHECK_THAT( 1.258930000000E-05, WithinRel( eiondistribution.outgoingEnergies()[8] ) );
  CHECK_THAT( 1.584900000000E-05, WithinRel( eiondistribution.outgoingEnergies()[9] ) );
  CHECK_THAT( 1.883650000000E-05, WithinRel( eiondistribution.outgoingEnergies()[10] ) );
  CHECK_THAT( 2.440620000000E-05, WithinRel( eiondistribution.outgoingEnergies()[11] ) );
  CHECK_THAT( 3.162280000000E-05, WithinRel( eiondistribution.outgoingEnergies()[12] ) );
  CHECK_THAT( 4.319500000000E-05, WithinRel( eiondistribution.outgoingEnergies()[13] ) );

  CHECK_THAT( 0.000000000000E+00, WithinRel( eiondistribution.cdf()[0] ) );
  CHECK_THAT( 7.331561116464E-02, WithinRel( eiondistribution.cdf()[1] ) );
  CHECK_THAT( 1.326897983815E-01, WithinRel( eiondistribution.cdf()[2] ) );
  CHECK_THAT( 2.239504599538E-01, WithinRel( eiondistribution.cdf()[3] ) );
  CHECK_THAT( 3.239408010297E-01, WithinRel( eiondistribution.cdf()[4] ) );
  CHECK_THAT( 4.457028360624E-01, WithinRel( eiondistribution.cdf()[5] ) );
  CHECK_THAT( 5.121432582477E-01, WithinRel( eiondistribution.cdf()[6] ) );
  CHECK_THAT( 6.122427030250E-01, WithinRel( eiondistribution.cdf()[7] ) );
  CHECK_THAT( 7.115063101586E-01, WithinRel( eiondistribution.cdf()[8] ) );
  CHECK_THAT( 7.742971020638E-01, WithinRel( eiondistribution.cdf()[9] ) );
  CHECK_THAT( 8.177487997791E-01, WithinRel( eiondistribution.cdf()[10] ) );
  CHECK_THAT( 8.785708761786E-01, WithinRel( eiondistribution.cdf()[11] ) );
  CHECK_THAT( 9.338664910728E-01, WithinRel( eiondistribution.cdf()[12] ) );
  CHECK_THAT( 1.000000000000E+00, WithinRel( eiondistribution.cdf()[13] ) );

  eiondistribution = chunk.EION( 1 ).distribution(8);
  CHECK_THAT( 1e+5, WithinRel( eiondistribution.energy() ) );
  CHECK( 147 == eiondistribution.numberOutgoingEnergies() );

  // BREME block - EPR data file
  CHECK( true == chunk.BREME().has_value() );

  CHECK( 10 == chunk.BREME()->NB() );
  CHECK( 10 == chunk.BREME()->numberEnergyPoints() );
  CHECK( 10 == chunk.BREME()->energies().size() );
  CHECK( 10 == chunk.BREME()->distributions().size() );

  auto bremdistribution = chunk.BREME()->distribution(1);
  CHECK_THAT( 1.000000000000E-05, WithinRel( bremdistribution.energy() ) );
  CHECK( 17 == bremdistribution.numberOutgoingEnergies() );

  bremdistribution = chunk.BREME()->distribution(2);
  CHECK_THAT( 2.073600E-05, WithinRel( bremdistribution.energy() ) );
  CHECK( 19 == bremdistribution.numberOutgoingEnergies() );

  CHECK_THAT( 1.000000000000E-07, WithinRel( bremdistribution.outgoingEnergies()[0] ) );
  CHECK_THAT( 1.460800000000E-07, WithinRel( bremdistribution.outgoingEnergies()[1] ) );
  CHECK_THAT( 1.941040000000E-07, WithinRel( bremdistribution.outgoingEnergies()[2] ) );
  CHECK_THAT( 2.402240000000E-07, WithinRel( bremdistribution.outgoingEnergies()[3] ) );
  CHECK_THAT( 3.307420000000E-07, WithinRel( bremdistribution.outgoingEnergies()[4] ) );
  CHECK_THAT( 4.553680000000E-07, WithinRel( bremdistribution.outgoingEnergies()[5] ) );
  CHECK_THAT( 6.652010000000E-07, WithinRel( bremdistribution.outgoingEnergies()[6] ) );
  CHECK_THAT( 8.838860000000E-07, WithinRel( bremdistribution.outgoingEnergies()[7] ) );
  CHECK_THAT( 1.093900000000E-06, WithinRel( bremdistribution.outgoingEnergies()[8] ) );
  CHECK_THAT( 1.506090000000E-06, WithinRel( bremdistribution.outgoingEnergies()[9] ) );
  CHECK_THAT( 2.073600000000E-06, WithinRel( bremdistribution.outgoingEnergies()[10] ) );
  CHECK_THAT( 2.932510000000E-06, WithinRel( bremdistribution.outgoingEnergies()[11] ) );
  CHECK_THAT( 4.147200000000E-06, WithinRel( bremdistribution.outgoingEnergies()[12] ) );
  CHECK_THAT( 5.865030000000E-06, WithinRel( bremdistribution.outgoingEnergies()[13] ) );
  CHECK_THAT( 8.294400000000E-06, WithinRel( bremdistribution.outgoingEnergies()[14] ) );
  CHECK_THAT( 1.173010000000E-05, WithinRel( bremdistribution.outgoingEnergies()[15] ) );
  CHECK_THAT( 1.658880000000E-05, WithinRel( bremdistribution.outgoingEnergies()[16] ) );
  CHECK_THAT( 2.052860000000E-05, WithinRel( bremdistribution.outgoingEnergies()[17] ) );
  CHECK_THAT( 2.073600000000E-05, WithinRel( bremdistribution.outgoingEnergies()[18] ) );

  CHECK_THAT( 0.000000000000E+00, WithinRel( bremdistribution.cdf()[0] ) );
  CHECK_THAT( 7.173043318075E-02, WithinRel( bremdistribution.cdf()[1] ) );
  CHECK_THAT( 1.249665748251E-01, WithinRel( bremdistribution.cdf()[2] ) );
  CHECK_THAT( 1.646566864984E-01, WithinRel( bremdistribution.cdf()[3] ) );
  CHECK_THAT( 2.247508182846E-01, WithinRel( bremdistribution.cdf()[4] ) );
  CHECK_THAT( 2.848391828607E-01, WithinRel( bremdistribution.cdf()[5] ) );
  CHECK_THAT( 3.565273694928E-01, WithinRel( bremdistribution.cdf()[6] ) );
  CHECK_THAT( 4.097170294934E-01, WithinRel( bremdistribution.cdf()[7] ) );
  CHECK_THAT( 4.493639981010E-01, WithinRel( bremdistribution.cdf()[8] ) );
  CHECK_THAT( 5.093809240389E-01, WithinRel( bremdistribution.cdf()[9] ) );
  CHECK_THAT( 5.693767769535E-01, WithinRel( bremdistribution.cdf()[10] ) );
  CHECK_THAT( 6.345683905906E-01, WithinRel( bremdistribution.cdf()[11] ) );
  CHECK_THAT( 6.997311655273E-01, WithinRel( bremdistribution.cdf()[12] ) );
  CHECK_THAT( 7.648297087129E-01, WithinRel( bremdistribution.cdf()[13] ) );
  CHECK_THAT( 8.298143855346E-01, WithinRel( bremdistribution.cdf()[14] ) );
  CHECK_THAT( 8.946128910962E-01, WithinRel( bremdistribution.cdf()[15] ) );
  CHECK_THAT( 9.591194227081E-01, WithinRel( bremdistribution.cdf()[16] ) );
  CHECK_THAT( 9.981726317539E-01, WithinRel( bremdistribution.cdf()[17] ) );
  CHECK_THAT( 1.000000000000E+00, WithinRel( bremdistribution.cdf()[18] ) );

  bremdistribution = chunk.BREME()->distribution(10);
  CHECK_THAT( 1e+5, WithinRel( bremdistribution.energy() ) );
  CHECK( 111 == bremdistribution.numberOutgoingEnergies() );

  // BREML block - EPR data file
  CHECK( true == chunk.BREML().has_value() );

  CHECK( 82 == chunk.BREML()->NBL() );
  CHECK( 82 == chunk.BREML()->numberEnergyPoints() );

  CHECK( 82 == chunk.BREML()->energies().size() );
  CHECK( 82 == chunk.BREML()->energyAfterBremsstrahlung().size() );

  CHECK_THAT( 1.000000000000E-05, WithinRel( chunk.BREML()->energies().front() ) );
  CHECK_THAT( 1.000000000000E+05, WithinRel( chunk.BREML()->energies().back() ) );

  CHECK_THAT( 7.855740000000E-06, WithinRel( chunk.BREML()->energyAfterBremsstrahlung().front() ) );
  CHECK_THAT( 9.733190000000E+04, WithinRel( chunk.BREML()->energyAfterBremsstrahlung().back() ) );

  // SELAS block - not eprdata14 file
  CHECK( false == chunk.SELAS().has_value() );
}

void verifyChunkEprdata14( const PhotoatomicTable& chunk ) {

  CHECK( "6000.14p" == chunk.ZAID() );
  CHECK_THAT( 0., WithinRel( chunk.temperature() ) );

  CHECK( 24009 == chunk.length() );
  CHECK( 0 == chunk.S() );
  CHECK( 0 == chunk.isomericState() );
  CHECK( 6 == chunk.Z() );
  CHECK( 6 == chunk.atomNumber() );
  CHECK( 0 == chunk.A() );
  CHECK( 0 == chunk.massNumber() );
  CHECK( 1210 == chunk.NES() );
  CHECK( 1210 == chunk.numberEnergyPoints() );
  CHECK( 0 == chunk.NFLO() );
  CHECK( 0 == chunk.numberFluorescenceEdges() );
  CHECK( 3 == chunk.NSH() );
  CHECK( 3 == chunk.numberElectronShells() );

  // this is an EPR data file
  CHECK( 3 == chunk.NEPR() );
  CHECK( 3 == chunk.electronPhotonRelaxationFormat() );
  CHECK( 4 == chunk.NSSH() );
  CHECK( 4 == chunk.numberElectronSubshells() );
  CHECK( 352 == chunk.NE() );
  CHECK( 352 == chunk.numberElectronEnergyPoints() );
  CHECK( 181 == chunk.NXL() );
  CHECK( 181 == chunk.numberElectronExcitationEnergyPoints() );
  CHECK( 16 == chunk.NA() );
  CHECK( 16 == chunk.numberElectronElasticEnergyPoints() );
  CHECK( 9 == chunk.NB() );
  CHECK( 9 == chunk.numberPhotonBremsstrahlungEnergyPoints() );
  CHECK( 75 == chunk.NBL() );
  CHECK( 75 == chunk.numberElectronBremsstrahlungEnergyPoints() );
  CHECK( 142 == chunk.NINC() );
  CHECK( 142 == chunk.numberIncoherentMomentumValues() );
  CHECK( 138 == chunk.NCOH() );
  CHECK( 138 == chunk.numberCoherentMomentumValues() );

  // ESZG block
  CHECK( false == chunk.ESZG().empty() );

  CHECK( 1210 == chunk.ESZG().NES() );
  CHECK( 1210 == chunk.ESZG().numberEnergyPoints() );

  CHECK( 1210 == chunk.ESZG().energies().size() );
  CHECK( 1210 == chunk.ESZG().incoherent().size() );
  CHECK( 1210 == chunk.ESZG().coherent().size() );
  CHECK( 1210 == chunk.ESZG().photoelectric().size() );
  CHECK( 1210 == chunk.ESZG().pairproduction().size() );

  CHECK_THAT( -1.381551055796E+01, WithinRel( chunk.ESZG().energies().front() ) );
  CHECK_THAT(  1.151292546497E+01, WithinRel( chunk.ESZG().energies().back() ) );
  CHECK_THAT( -1.508068523402E+01, WithinRel( chunk.ESZG().incoherent().front() ) );
  CHECK_THAT( -9.187600885007E+00, WithinRel( chunk.ESZG().incoherent().back() ) );
  CHECK_THAT( -9.890915512852E+00, WithinRel( chunk.ESZG().coherent().front() ) );
  CHECK_THAT( -3.019653583318E+01, WithinRel( chunk.ESZG().coherent().back() ) );
  CHECK_THAT(                   0, WithinRel( chunk.ESZG().photoelectric().front() ) );
  CHECK_THAT( -2.312511362096E+01, WithinRel( chunk.ESZG().photoelectric().back() ) );
  CHECK_THAT(                   0, WithinRel( chunk.ESZG().pairproduction().front() ) );
  CHECK_THAT( -1.024627895579E+00, WithinRel( chunk.ESZG().pairproduction().back() ) );

  // JINC block
  CHECK( false == chunk.JINC().empty() );

  CHECK( 142 == chunk.JINC().NM() );
  CHECK( 142 == chunk.JINC().numberValues() );

  CHECK( 142 == chunk.JINC().momentum().size() );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.JINC().momentum().front() ) );
  CHECK_THAT( 1.000000000000E+09, WithinRel( chunk.JINC().momentum().back() ) );

  CHECK( 142 == chunk.JINC().values().size() );
  CHECK_THAT( 0, WithinRel( chunk.JINC().values().front() ) );
  CHECK_THAT( 6, WithinRel( chunk.JINC().values().back() ) );

  // JCOH block
  CHECK( false == chunk.JCOH().empty() );

  CHECK( 138 == chunk.JCOH().NM() );
  CHECK( 138 == chunk.JCOH().numberValues() );

  CHECK( 138 == chunk.JCOH().momentum().size() );
  CHECK_THAT( 0.                , WithinRel( chunk.JCOH().momentum().front() ) );
  CHECK_THAT( 1.000000000000E+09, WithinRel( chunk.JCOH().momentum().back() ) );

  CHECK( 138 == chunk.JCOH().integratedFormFactors().size() );
  CHECK_THAT( 0.                , WithinRel( chunk.JCOH().integratedFormFactors().front() ) );
  CHECK_THAT( 1.390418232150E-01, WithinRel( chunk.JCOH().integratedFormFactors().back() ) );

  CHECK( 138 == chunk.JCOH().formFactors().size() );
  CHECK_THAT( 6.                , WithinRel( chunk.JCOH().formFactors().front() ) );
  CHECK_THAT( 1.681000000000E-29, WithinRel( chunk.JCOH().formFactors().back() ) );

  // JFLO block
  CHECK( false == chunk.JFLO().has_value() );

  // LHNM block
  CHECK( false == chunk.LHNM().empty() );

  CHECK( 1210 == chunk.LHNM().NES() );
  CHECK( 1210 == chunk.LHNM().numberEnergyPoints() );
  CHECK( 1210 == chunk.LHNM().heating().size() );

  CHECK_THAT( 9.318532129105E-07, WithinRel( chunk.LHNM().heating().front() ) );
  CHECK_THAT( 9.999615968030E+04, WithinRel( chunk.LHNM().heating().back() ) );

  // EPS block
  CHECK( false == chunk.EPS()->empty() );

  CHECK( 3 == chunk.EPS()->NSH() );
  CHECK( 3 == chunk.EPS()->numberElectronShells() );

  CHECK( 2 == chunk.EPS()->numberElectrons()[0] );
  CHECK_THAT( 2.847000000000E-04, WithinRel( chunk.EPS()->bindingEnergies()[0] ) );
  CHECK_THAT( 3.333333333333E-01, WithinRel( chunk.EPS()->interactionProbabilities()[0] ) );

  CHECK( 2 == chunk.EPS()->numberElectrons()[2] );
  CHECK_THAT( 0.000000000000e+00, WithinRel( chunk.EPS()->bindingEnergies()[2] ) );
  CHECK_THAT( 1.000000000000e+00, WithinRel( chunk.EPS()->interactionProbabilities()[2] ) );

  CHECK( 2 == chunk.EPS()->numberElectronsPerShell( 1 ) );
  CHECK_THAT( 2.847000000000E-04, WithinRel( chunk.EPS()->bindingEnergy( 1 ) ) );
  CHECK_THAT( 3.333333333333E-01, WithinRel( chunk.EPS()->interactionProbability( 1 ) ) );

  CHECK( 2 == chunk.EPS()->numberElectronsPerShell( 3 ) );
  CHECK_THAT( 0.000000000000e+00, WithinRel( chunk.EPS()->bindingEnergy( 3 ) ) );
  CHECK_THAT( 1.000000000000e+00, WithinRel( chunk.EPS()->interactionProbability( 3 ) ) );

  // SWD block
  CHECK( false == chunk.SWD()->empty() );

  CHECK( 3 == chunk.SWD()->NSH() );

  CHECK( 1 == chunk.SWD()->LSWD( 1 ) );
  CHECK( 96 == chunk.SWD()->LSWD( 2 ) );
  CHECK( 191 == chunk.SWD()->LSWD( 3 ) );

  auto profile = chunk.SWD()->comptonProfile(1);
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK_THAT( 0., WithinRel( profile.momentum().front() ) );
  CHECK_THAT( 100., WithinRel( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK_THAT( 3.029773669016E-01, WithinRel( profile.pdf().front() ) );
  CHECK_THAT( 1.148541652307E-08, WithinRel( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK_THAT( 0., WithinRel( profile.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( profile.cdf().back() ) );

  profile = chunk.SWD()->comptonProfile(3);
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK_THAT( 0., WithinRel( profile.momentum().front() ) );
  CHECK_THAT( 100., WithinRel( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK_THAT( 9.711214568747E-01, WithinRel( profile.pdf().front() ) );
  CHECK_THAT( 1.592002388319E-13, WithinRel( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK_THAT( 0., WithinRel( profile.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( profile.cdf().back() ) );

  // SUBSH block - EPR data file
  CHECK( true == chunk.SUBSH().has_value() );

  CHECK( 4 == chunk.SUBSH()->NSSH() );
  CHECK( 4 == chunk.SUBSH()->numberElectronSubshells() );

  CHECK( 1 == chunk.SUBSH()->ID()[0] );
  CHECK( 2 == chunk.SUBSH()->ID()[1] );
  CHECK( 3 == chunk.SUBSH()->ID()[2] );
  CHECK( 4 == chunk.SUBSH()->ID()[3] );
  CHECK( 1 == chunk.SUBSH()->designators()[0] );
  CHECK( 2 == chunk.SUBSH()->designators()[1] );
  CHECK( 3 == chunk.SUBSH()->designators()[2] );
  CHECK( 4 == chunk.SUBSH()->designators()[3] );

  CHECK( 2 == chunk.SUBSH()->EP()[0] );
  CHECK( 2 == chunk.SUBSH()->EP()[1] );
  CHECK( 0.67 == chunk.SUBSH()->EP()[2] );
  CHECK( 1.33 == chunk.SUBSH()->EP()[3] );
  CHECK( 2 == chunk.SUBSH()->populations()[0] );
  CHECK( 2 == chunk.SUBSH()->populations()[1] );
  CHECK( 0.67 == chunk.SUBSH()->populations()[2] );
  CHECK( 1.33 == chunk.SUBSH()->populations()[3] );

  CHECK_THAT( 2.910100000000E-04, WithinRel( chunk.SUBSH()->BE()[0] ) );
  CHECK_THAT( 1.756000000000E-05, WithinRel( chunk.SUBSH()->BE()[1] ) );
  CHECK_THAT( 8.990000000000E-06, WithinRel( chunk.SUBSH()->BE()[2] ) );
  CHECK_THAT( 8.980000000000E-06, WithinRel( chunk.SUBSH()->BE()[3] ) );
  CHECK_THAT( 2.910100000000E-04, WithinRel( chunk.SUBSH()->bindingEnergies()[0] ) );
  CHECK_THAT( 1.756000000000E-05, WithinRel( chunk.SUBSH()->bindingEnergies()[1] ) );
  CHECK_THAT( 8.990000000000E-06, WithinRel( chunk.SUBSH()->bindingEnergies()[2] ) );
  CHECK_THAT( 8.980000000000E-06, WithinRel( chunk.SUBSH()->bindingEnergies()[3] ) );

  CHECK_THAT( 3.333333333333E-01, WithinRel( chunk.SUBSH()->CV()[0] ) );
  CHECK_THAT( 6.666666666667E-01, WithinRel( chunk.SUBSH()->CV()[1] ) );
  CHECK_THAT( 7.783333333333E-01, WithinRel( chunk.SUBSH()->CV()[2] ) );
  CHECK_THAT( 1.000000000000E+00, WithinRel( chunk.SUBSH()->CV()[3] ) );
  CHECK_THAT( 3.333333333333E-01, WithinRel( chunk.SUBSH()->vacancyProbabilities()[0] ) );
  CHECK_THAT( 6.666666666667E-01, WithinRel( chunk.SUBSH()->vacancyProbabilities()[1] ) );
  CHECK_THAT( 7.783333333333E-01, WithinRel( chunk.SUBSH()->vacancyProbabilities()[2] ) );
  CHECK_THAT( 1.000000000000E+00, WithinRel( chunk.SUBSH()->vacancyProbabilities()[3] ) );

  CHECK( 8 == chunk.SUBSH()->NT()[0] );
  CHECK( 0 == chunk.SUBSH()->NT()[1] );
  CHECK( 0 == chunk.SUBSH()->NT()[2] );
  CHECK( 0 == chunk.SUBSH()->NT()[3] );
  CHECK( 8 == chunk.SUBSH()->numberTransitions()[0] );
  CHECK( 0 == chunk.SUBSH()->numberTransitions()[1] );
  CHECK( 0 == chunk.SUBSH()->numberTransitions()[2] );
  CHECK( 0 == chunk.SUBSH()->numberTransitions()[3] );

  CHECK( 1 == chunk.SUBSH()->designator( 1 ) );
  CHECK( 4 == chunk.SUBSH()->designator( 4 ) );

  CHECK( 2 == chunk.SUBSH()->population( 1 ) );
  CHECK_THAT( 1.33, WithinRel( chunk.SUBSH()->population( 4 ) ) );

  CHECK_THAT( 2.910100000000E-04, WithinRel( chunk.SUBSH()->bindingEnergy( 1 ) ) );
  CHECK_THAT( 8.980000000000E-06, WithinRel( chunk.SUBSH()->bindingEnergy( 4 ) ) );

  CHECK_THAT( 3.333333333333E-01, WithinRel( chunk.SUBSH()->vacancyProbability( 1 ) ) );
  CHECK_THAT( 1., WithinRel( chunk.SUBSH()->vacancyProbability( 4 ) ) );

  CHECK( 8 == chunk.SUBSH()->numberTransitions( 1 ) );
  CHECK( 0 == chunk.SUBSH()->numberTransitions( 4 ) );

  // SPHEL block - EPR data file
  CHECK( true == chunk.SPHEL().has_value() );

  CHECK( 1210 == chunk.SPHEL()->NES() );
  CHECK( 1210 == chunk.SPHEL()->numberEnergyPoints() );
  CHECK( 4 == chunk.SPHEL()->NSSH() );
  CHECK( 4 == chunk.SPHEL()->numberElectronSubshells() );

  CHECK( 1210 == chunk.SPHEL()->photoelectric(1).size() );
  CHECK( 1210 == chunk.SPHEL()->photoelectric(2).size() );
  CHECK( 1210 == chunk.SPHEL()->photoelectric(3).size() );
  CHECK( 1210 == chunk.SPHEL()->photoelectric(4).size() );

  CHECK_THAT(  0.000000000000E+00, WithinRel( chunk.SPHEL()->photoelectric(1).front() ) );
  CHECK_THAT( -2.317697619097E+01, WithinRel( chunk.SPHEL()->photoelectric(1).back() ) );
  CHECK_THAT(  0.000000000000E+00, WithinRel( chunk.SPHEL()->photoelectric(2).front() ) );
  CHECK_THAT( -2.611037070231E+01, WithinRel( chunk.SPHEL()->photoelectric(2).back() ) );
  CHECK_THAT(  0.000000000000E+00, WithinRel( chunk.SPHEL()->photoelectric(3).front() ) );
  CHECK_THAT( -3.548663519625E+01, WithinRel( chunk.SPHEL()->photoelectric(3).back() ) );
  CHECK_THAT(  0.000000000000E+00, WithinRel( chunk.SPHEL()->photoelectric(4).front() ) );
  CHECK_THAT( -3.465159800880E+01, WithinRel( chunk.SPHEL()->photoelectric(4).back() ) );

  // XPROB block - EPR data file
  CHECK( true == chunk.XPROB().has_value() );

  CHECK( 4 == chunk.XPROB()->NSSH() );
  CHECK( 4 == chunk.XPROB()->numberElectronSubshells() );
  CHECK( 4 == chunk.XPROB()->data().size() );

  CHECK(  1 == chunk.XPROB()->LTRAN(1) );
  CHECK( 33 == chunk.XPROB()->LTRAN(2) );
  CHECK( 33 == chunk.XPROB()->LTRAN(3) );
  CHECK( 33 == chunk.XPROB()->LTRAN(4) );
  CHECK(  1 == chunk.XPROB()->transitionDataLocator(1) );
  CHECK( 33 == chunk.XPROB()->transitionDataLocator(2) );
  CHECK( 33 == chunk.XPROB()->transitionDataLocator(3) );
  CHECK( 33 == chunk.XPROB()->transitionDataLocator(4) );

  CHECK( 8 == chunk.XPROB()->transitionData(1).NT() );
  CHECK( 8 == chunk.XPROB()->transitionData(1).numberTransitions() );

  CHECK( 4 == chunk.XPROB()->transitionData(1).transition(1).size() );
  CHECK( 4 == chunk.XPROB()->transitionData(1).transition(8).size() );

  CHECK_THAT( 3, WithinRel( chunk.XPROB()->transitionData(1).transition(1)[0] ) );
  CHECK_THAT( 0, WithinRel( chunk.XPROB()->transitionData(1).transition(1)[1] ) );
  CHECK_THAT( 2.820200000000E-04, WithinRel( chunk.XPROB()->transitionData(1).transition(1)[2] ) );
  CHECK_THAT( 5.614877933725E-04, WithinRel( chunk.XPROB()->transitionData(1).transition(1)[3] ) );
  CHECK_THAT( 4, WithinRel( chunk.XPROB()->transitionData(1).transition(8)[0] ) );
  CHECK_THAT( 4, WithinRel( chunk.XPROB()->transitionData(1).transition(8)[1] ) );
  CHECK_THAT( 2.730500000000E-04, WithinRel( chunk.XPROB()->transitionData(1).transition(8)[2] ) );
  CHECK_THAT( 1.000000000000E+00, WithinRel( chunk.XPROB()->transitionData(1).transition(8)[3] ) );

  CHECK( 3 == chunk.XPROB()->transitionData(1).primaryDesignator(1) );
  CHECK( 0 == chunk.XPROB()->transitionData(1).secondaryDesignator(1) );
  CHECK_THAT( 2.820200000000E-04, WithinRel( chunk.XPROB()->transitionData(1).energy(1) ) );
  CHECK_THAT( 5.614877933725E-04, WithinRel( chunk.XPROB()->transitionData(1).probability(1) ) );
  CHECK( 4 == chunk.XPROB()->transitionData(1).primaryDesignator(8) );
  CHECK( 4 == chunk.XPROB()->transitionData(1).secondaryDesignator(8) );
  CHECK_THAT( 2.730500000000E-04, WithinRel( chunk.XPROB()->transitionData(1).energy(8) ) );
  CHECK_THAT( 1.000000000000E+00, WithinRel( chunk.XPROB()->transitionData(1).probability(8) ) );

  CHECK( true == chunk.XPROB()->transitionData(1).isRadiativeTransition(1) );
  CHECK( false == chunk.XPROB()->transitionData(1).isRadiativeTransition(8) );

  CHECK( true == chunk.XPROB()->transitionData(2).empty() );
  CHECK( true == chunk.XPROB()->transitionData(3).empty() );
  CHECK( true == chunk.XPROB()->transitionData(4).empty() );

  // ESZE block - EPR data file
  CHECK( true == chunk.ESZE().has_value() );

  CHECK( 352 == chunk.ESZE()->NE() );
  CHECK( 352 == chunk.ESZE()->numberEnergyPoints() );
  CHECK( 4 == chunk.ESZE()->NSSH() );
  CHECK( 4 == chunk.ESZE()->numberElectronSubshells() );

  CHECK( 352 == chunk.ESZE()->energies().size() );
  CHECK( 352 == chunk.ESZE()->total().size() );
  CHECK( 352 == chunk.ESZE()->elastic().size() );
  CHECK( 352 == chunk.ESZE()->bremsstrahlung().size() );
  CHECK( 352 == chunk.ESZE()->excitation().size() );
  CHECK( 352 == chunk.ESZE()->totalElectroionisation().size() );
  CHECK( 352 == chunk.ESZE()->electroionisation(1).size() );
  CHECK( 352 == chunk.ESZE()->electroionisation(2).size() );
  CHECK( 352 == chunk.ESZE()->electroionisation(3).size() );
  CHECK( 352 == chunk.ESZE()->electroionisation(4).size() );

  CHECK_THAT( 1.000000000000E-05, WithinRel( chunk.ESZE()->energies().front() ) );
  CHECK_THAT( 1.000000000000E+05, WithinRel( chunk.ESZE()->energies().back() ) );
  CHECK_THAT( 3.098128233128E+09, WithinRel( chunk.ESZE()->total().front() ) );
  CHECK_THAT( 5.118768719723E+05, WithinRel( chunk.ESZE()->total().back() ) );
  CHECK_THAT( 3.063510000000E+09, WithinRel( chunk.ESZE()->elastic().front() ) );
  CHECK_THAT( 4.723090000000E-04, WithinRel( chunk.ESZE()->elastic().back() ) );
  CHECK_THAT( 6.031280000000E+02, WithinRel( chunk.ESZE()->bremsstrahlung().front() ) );
  CHECK_THAT( 1.697150000000E+01, WithinRel( chunk.ESZE()->bremsstrahlung().back() ) );
  CHECK_THAT( 3.168630000000E+06, WithinRel( chunk.ESZE()->excitation().front() ) );
  CHECK_THAT( 1.198920000000E+05, WithinRel( chunk.ESZE()->excitation().back() ) );
  CHECK_THAT( 3.144900000000E+07, WithinRel( chunk.ESZE()->totalElectroionisation().front() ) );
  CHECK_THAT( 3.919679000000E+05, WithinRel( chunk.ESZE()->totalElectroionisation().back() ) );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.ESZE()->electroionisation(1).front() ) );
  CHECK_THAT( 1.338050000000E+04, WithinRel( chunk.ESZE()->electroionisation(1).back() ) );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.ESZE()->electroionisation(2).front() ) );
  CHECK_THAT( 7.595140000000E+04, WithinRel( chunk.ESZE()->electroionisation(2).back() ) );
  CHECK_THAT( 1.041970000000E+07, WithinRel( chunk.ESZE()->electroionisation(3).front() ) );
  CHECK_THAT( 1.009350000000E+05, WithinRel( chunk.ESZE()->electroionisation(3).back() ) );
  CHECK_THAT( 2.102930000000E+07, WithinRel( chunk.ESZE()->electroionisation(4).front() ) );
  CHECK_THAT( 2.017010000000E+05, WithinRel( chunk.ESZE()->electroionisation(4).back() ) );

  // EXCIT block - EPR data file
  CHECK( true == chunk.EXCIT().has_value() );

  CHECK( 181 == chunk.EXCIT()->NXL() );
  CHECK( 181 == chunk.EXCIT()->numberEnergyPoints() );

  CHECK( 181 == chunk.EXCIT()->energies().size() );
  CHECK( 181 == chunk.EXCIT()->excitationEnergyLoss().size() );

  CHECK_THAT( 1.000000000000E-05, WithinRel( chunk.EXCIT()->energies().front() ) );
  CHECK_THAT( 1.000000000000E+05, WithinRel( chunk.EXCIT()->energies().back() ) );

  CHECK_THAT( 9.232690000000E-06, WithinRel( chunk.EXCIT()->excitationEnergyLoss().front() ) );
  CHECK_THAT( 1.981540000000E-05, WithinRel( chunk.EXCIT()->excitationEnergyLoss().back() ) );

  // ELAS block - EPR data file
  CHECK( true == chunk.ELAS().has_value() );

  CHECK( 16 == chunk.ELAS()->NA() );
  CHECK( 16 == chunk.ELAS()->numberEnergyPoints() );
  CHECK( 16 == chunk.ELAS()->energies().size() );
  CHECK( 16 == chunk.ELAS()->distributions().size() );

  auto distribution = chunk.ELAS()->distribution(1);
  CHECK( 1.000000000000E-05 == distribution.energy() );
  CHECK( 2 == distribution.numberCosines() );

  distribution = chunk.ELAS()->distribution(16);
  CHECK( 1e+5 == distribution.energy() );
  CHECK( 96 == distribution.numberCosines() );

  // EION block - EPR data file
  CHECK( false == chunk.EION( 1 ).empty() );
  CHECK( false == chunk.EION( 2 ).empty() );
  CHECK( false == chunk.EION( 3 ).empty() );
  CHECK( false == chunk.EION( 4 ).empty() );

  CHECK( 7 == chunk.EION( 1 ).NB() );
  CHECK( 7 == chunk.EION( 1 ).numberEnergyPoints() );
  CHECK( 7 == chunk.EION( 1 ).energies().size() );
  CHECK( 7 == chunk.EION( 1 ).distributions().size() );

  auto eiondistribution = chunk.EION( 1 ).distribution(1);
  CHECK( 2.910100000000E-04 == eiondistribution.energy() );
  CHECK( 2 == eiondistribution.numberOutgoingEnergies() );

  eiondistribution = chunk.EION( 1 ).distribution(7);
  CHECK( 1e+5 == eiondistribution.energy() );
  CHECK( 128 == eiondistribution.numberOutgoingEnergies() );

  eiondistribution = chunk.EION( 4 ).distribution(1);
  CHECK( 8.980000000000E-06 == eiondistribution.energy() );
  CHECK( 2 == eiondistribution.numberOutgoingEnergies() );

  eiondistribution = chunk.EION( 4 ).distribution(8);
  CHECK( 1e+5 == eiondistribution.energy() );
  CHECK( 143 == eiondistribution.numberOutgoingEnergies() );

  // BREME block - EPR data file
  CHECK( true == chunk.BREME().has_value() );

  CHECK( 9 == chunk.BREME()->NB() );
  CHECK( 9 == chunk.BREME()->numberEnergyPoints() );
  CHECK( 9 == chunk.BREME()->energies().size() );
  CHECK( 9 == chunk.BREME()->distributions().size() );

  auto bremdistribution = chunk.BREME()->distribution(1);
  CHECK( 1.000000000000E-05 == bremdistribution.energy() );
  CHECK( 17 == bremdistribution.numberOutgoingEnergies() );

  bremdistribution = chunk.BREME()->distribution(9);
  CHECK( 1e+5 == bremdistribution.energy() );
  CHECK( 105 == bremdistribution.numberOutgoingEnergies() );

  // BREML block - EPR data file
  CHECK( true == chunk.BREML().has_value() );

  CHECK( 75 == chunk.BREML()->NBL() );
  CHECK( 75 == chunk.BREML()->numberEnergyPoints() );

  CHECK( 75 == chunk.BREML()->energies().size() );
  CHECK( 75 == chunk.BREML()->energyAfterBremsstrahlung().size() );

  CHECK_THAT( 1.000000000000E-05, WithinRel( chunk.BREML()->energies().front() ) );
  CHECK_THAT( 1.000000000000E+05, WithinRel( chunk.BREML()->energies().back() ) );

  CHECK_THAT( 2.150380000000E-06, WithinRel( chunk.BREML()->energyAfterBremsstrahlung().front() ) );
  CHECK_THAT( 2.712000000000E+03, WithinRel( chunk.BREML()->energyAfterBremsstrahlung().back() ) );

  // SELAS block - EPR data file
  CHECK( true == chunk.SELAS().has_value() );

  CHECK( 352 == chunk.SELAS()->NE() );
  CHECK( 352 == chunk.SELAS()->numberEnergyPoints() );

  CHECK( 352 == chunk.SELAS()->transport().size() );
  CHECK( 352 == chunk.SELAS()->total().size() );

  CHECK_THAT( 3.063510000000E+09, WithinRel( chunk.SELAS()->transport().front() ) );
  CHECK_THAT( 1.510140000000E-08, WithinRel( chunk.SELAS()->transport().back() ) );

  CHECK_THAT( 3.063510000000E+09, WithinRel( chunk.SELAS()->total().front() ) );
  CHECK_THAT( 1.407220000000E+05, WithinRel( chunk.SELAS()->total().back() ) );
}
