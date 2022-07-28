#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

void verifyChunkMcplib( const PhotoatomicTable& );
void verifyChunkMcplib03( const PhotoatomicTable& );

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

    WHEN( "constructing a PhotoatomicTable from its components" ) {

      PhotoatomicTable base( std::move( table ) );

      PhotoatomicTable chunk( 1, base.header(),
                              { 1001, 1002, 1003 },
                              { 0.999167, 1.996800, 2.990140 },
                              base.ESZG(), base.JINC(),
                              base.JCOH(), base.LHNM(),
                              std::nullopt,
                              std::nullopt,
                              std::nullopt );

      THEN( "a PhotoatomicTable can be constructed and members can be "
            "tested" ) {

        verifyChunkMcplib( chunk );
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

    WHEN( "constructing a PhotoatomicTable from its components" ) {

      PhotoatomicTable base( std::move( table ) );

      PhotoatomicTable chunk( 3, base.header(),
                              {  },
                              {  },
                              base.ESZG(), base.JINC(),
                              base.JCOH(), base.LHNM(),
                              std::nullopt,
                              base.EPS(), base.SWD() );

      THEN( "a PhotoatomicTable can be constructed and members can be "
            "tested" ) {

        verifyChunkMcplib03( chunk );
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

void verifyChunkMcplib( const PhotoatomicTable& chunk ) {

  CHECK( "1000.01p" == chunk.ZAID() );
  CHECK( 0. == Approx( chunk.temperature() ) );

  CHECK( 389 == chunk.length() );
  CHECK( 43 == chunk.NES() );
  CHECK( 43 == chunk.numberEnergyPoints() );
  CHECK( 0 == chunk.NFLO() );
  CHECK( 0 == chunk.numberFluorescenceEdges() );
  CHECK( 0 == chunk.NSH() );
  CHECK( 0 == chunk.numberElectronShells() );

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

  // JFLO block
  CHECK( std::nullopt == chunk.JFLO() );

  // LHNM block
  CHECK( false == chunk.LHNM().empty() );

  CHECK( 43 == chunk.LHNM().NES() );
  CHECK( 43 == chunk.LHNM().numberEnergyPoints() );
  CHECK( 43 == chunk.LHNM().heating().size() );

  CHECK( 9.457315870945E-04 == Approx( chunk.LHNM().heating().front() ) );
  CHECK( 9.086036433693E+01 == Approx( chunk.LHNM().heating().back() ) );

  // EPS block
  CHECK( std::nullopt == chunk.EPS() );

  // SWD block
  CHECK( std::nullopt == chunk.SWD() );
}

void verifyChunkMcplib03( const PhotoatomicTable& chunk ) {

  CHECK( "3000.03p" == chunk.ZAID() );
  CHECK( 0. == Approx( chunk.temperature() ) );

  CHECK( 821 == chunk.length() );
  CHECK( 82 == chunk.NES() );
  CHECK( 82 == chunk.numberEnergyPoints() );
  CHECK( 0 == chunk.NFLO() );
  CHECK( 0 == chunk.numberFluorescenceEdges() );
  CHECK( 2 == chunk.NSH() );
  CHECK( 2 == chunk.numberElectronShells() );

  // ESZG block
  CHECK( false == chunk.ESZG().empty() );

  CHECK( 82 == chunk.ESZG().NES() );
  CHECK( 82 == chunk.ESZG().numberEnergyPoints() );

  CHECK( 82 == chunk.ESZG().energies().size() );
  CHECK( 82 == chunk.ESZG().incoherent().size() );
  CHECK( 82 == chunk.ESZG().coherent().size() );
  CHECK( 82 == chunk.ESZG().photoelectric().size() );
  CHECK( 82 == chunk.ESZG().pairproduction().size() );

  CHECK( -6.907755278982E+00 == Approx( chunk.ESZG().energies().front() ) );
  CHECK(  1.151292546497E+01 == Approx( chunk.ESZG().energies().back() ) );
  CHECK( -1.036037569528E+00 == Approx( chunk.ESZG().incoherent().front() ) );
  CHECK( -9.880667912376E+00 == Approx( chunk.ESZG().incoherent().back() ) );
  CHECK(  1.556749961755E+00 == Approx( chunk.ESZG().coherent().front() ) );
  CHECK( -3.192069466597E+01 == Approx( chunk.ESZG().coherent().back() ) );
  CHECK(  7.753623546560E+00 == Approx( chunk.ESZG().photoelectric().front() ) );
  CHECK( -2.663665884863E+01 == Approx( chunk.ESZG().photoelectric().back() ) );
  CHECK(                   0 == Approx( chunk.ESZG().pairproduction().front() ) );
  CHECK( -2.222019445154E+00 == Approx( chunk.ESZG().pairproduction().back() ) );

  // JINC block
  CHECK( false == chunk.JINC().empty() );

  CHECK( 21 == chunk.JINC().NM() );
  CHECK( 21 == chunk.JINC().numberValues() );

  CHECK( 21 == chunk.JINC().momentum().size() );
  CHECK( 0.   == Approx( chunk.JINC().momentum().front() ) );
  CHECK( 8.   == Approx( chunk.JINC().momentum().back() ) );

  CHECK( 21 == chunk.JINC().values().size() );
  CHECK( 0 == Approx( chunk.JINC().values().front() ) );
  CHECK( 3 == Approx( chunk.JINC().values().back() ) );

  // JCOH block
  CHECK( false == chunk.JCOH().empty() );

  CHECK( 55 == chunk.JCOH().NM() );
  CHECK( 55 == chunk.JCOH().numberValues() );

  CHECK( 55 == chunk.JCOH().momentum().size() );
  CHECK( 0.   == Approx( chunk.JCOH().momentum().front() ) );
  CHECK( 6.   == Approx( chunk.JCOH().momentum().back() ) );

  CHECK( 55 == chunk.JCOH().integratedFormFactors().size() );
  CHECK( 0. == Approx( chunk.JCOH().integratedFormFactors().front() ) );
  CHECK( 9.972763100947E-02 == Approx( chunk.JCOH().integratedFormFactors().back() ) );

  CHECK( 55 == chunk.JCOH().formFactors().size() );
  CHECK( 3. == Approx( chunk.JCOH().formFactors().front() ) );
  CHECK( 7.806310000000E-04 == Approx( chunk.JCOH().formFactors().back() ) );

  // JFLO block
  CHECK( std::nullopt == chunk.JFLO() );

  // LHNM block
  CHECK( false == chunk.LHNM().empty() );

  CHECK( 82 == chunk.LHNM().NES() );
  CHECK( 82 == chunk.LHNM().numberEnergyPoints() );
  CHECK( 82 == chunk.LHNM().heating().size() );

  CHECK( 9.978170710722E-04 == Approx( chunk.LHNM().heating().front() ) );
  CHECK( 9.999428234605E+04 == Approx( chunk.LHNM().heating().back() ) );

  // EPS block
  CHECK( false == chunk.EPS()->empty() );

  CHECK( 2 == chunk.EPS()->NSH() );
  CHECK( 2 == chunk.EPS()->numberElectronShells() );

  CHECK( 2 == Approx( chunk.EPS()->numberElectrons()[0] ) );
  CHECK( 1 == Approx( chunk.EPS()->numberElectrons()[1] ) );
  CHECK( 5.480000000000e-05 == Approx( chunk.EPS()->bindingEnergies()[0] ) );
  CHECK( 1.000000000000e-06 == Approx( chunk.EPS()->bindingEnergies()[1] ) );
  CHECK( 6.666666666667e-01 == Approx( chunk.EPS()->interactionProbabilities()[0] ) );
  CHECK( 3.333333333333e-01 == Approx( chunk.EPS()->interactionProbabilities()[1] ) );

  CHECK( 2 == chunk.EPS()->numberElectronsPerShell( 1 ) );
  CHECK( 1 == chunk.EPS()->numberElectronsPerShell( 2 ) );
  CHECK( 5.480000000000e-05 == Approx( chunk.EPS()->bindingEnergy( 1 ) ) );
  CHECK( 1.000000000000e-06 == Approx( chunk.EPS()->bindingEnergy( 2 ) ) );
  CHECK( 6.666666666667e-01 == Approx( chunk.EPS()->interactionProbability( 1 ) ) );
  CHECK( 3.333333333333e-01 == Approx( chunk.EPS()->interactionProbability( 2 ) ) );

  // SWD block
  CHECK( false == chunk.SWD()->empty() );

  CHECK( 2 == chunk.SWD()->NSH() );

  CHECK( 1 == chunk.SWD()->LSWD( 1 ) );
  CHECK( 96 == chunk.SWD()->LSWD( 2 ) );

  auto profile = chunk.SWD()->comptonProfile(1);
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK( 0. == Approx( profile.momentum().front() ) );
  CHECK( 100. == Approx( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK( 6.527863344596e-01 == Approx( profile.pdf().front() ) );
  CHECK( 3.571475386101e-10 == Approx( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK( 0. == Approx( profile.cdf().front() ) );
  CHECK( 1. == Approx( profile.cdf().back() ) );

  profile = chunk.SWD()->comptonProfile(2);
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK( 0. == Approx( profile.momentum().front() ) );
  CHECK( 100. == Approx( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK( 3.848272047027e+00 == Approx( profile.pdf().front() ) );
  CHECK( 8.728039694288e-12 == Approx( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK( 0. == Approx( profile.cdf().front() ) );
  CHECK( 1. == Approx( profile.cdf().back() ) );
}
