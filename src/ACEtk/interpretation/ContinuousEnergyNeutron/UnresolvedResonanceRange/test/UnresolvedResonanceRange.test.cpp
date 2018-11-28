#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;
using namespace dimwits;

SCENARIO( "Constructing UnresolvedResonanceRange" ){
  int INTT{ 2 };
  int ILF{ 102 };
  int IOA{ 18 };
  int IFF{ 0 };
  std::vector< double > energies{ 1.0, 3.0, 4.2 };
  std::vector< double > ptables{{
    0.3, 1.0, 2.0, 3.0, 4.0, 6.0,
    0.3, 1.1, 2.1, 3.1, 4.1, 6.1,
    0.4, 1.2, 2.2, 3.2, 4.2, 6.2,
  }};

  GIVEN( "valid input parameters" ){

    std::vector< int > validINTT{ 2, 5 };
    std::vector< int > validIFF{ 0, 1 };
    for( auto intt : validINTT ) {
      for( auto iff : validIFF ) {
        WHEN( "INTTT = " + std::to_string( intt ) + 
             " and IFF = " + std::to_string( iff ) ){
          ContinuousEnergyNeutron::UnresolvedResonanceRange UNR{ 
            intt, ILF, IOA, iff, energies, ptables };

          THEN( "the values can be verified" ){
            CHECK( intt == UNR.INTT() );
            CHECK( intt == UNR.interpolationParameter() );

            CHECK( ILF == UNR.ILF() );
            CHECK( ILF == UNR.inelasticCompetition() );

            CHECK( IOA == UNR.IOA() );
            CHECK( IOA == UNR.otherAbsorption() );

            CHECK( iff == UNR.IFF() );
            CHECK( iff == UNR.factors() );

            CHECK( ranges::equal( energies, UNR.incidentEnergies() ) );

            // for( auto cdf : UNR.CDF() ){
            //   std::cout << cdf << std::endl;
            // }
            CHECK( ranges::equal( {0.3, 0.3, 0.4}, UNR.CDF() ) );
            CHECK( ranges::equal( {1.0, 1.1, 1.2}, UNR.totalXS() ) );
            CHECK( ranges::equal( {2.0, 2.1, 2.2}, UNR.elasticXS() ) );
            CHECK( ranges::equal( {3.0, 3.1, 3.2}, UNR.fissionXS() ) );
            CHECK( ranges::equal( {4.0, 4.1, 4.2}, UNR.captureXS() ) );
            CHECK( ranges::equal( {6.0, 6.1, 6.2}, UNR.heating() ) );

            auto refTables = ptables | ranges::view::chunk( 6 );

            int pIndex = 0;

            auto pTable = UNR.probabilityTables()[ pIndex ];
            CHECK( refTables[ pIndex ][ 0 ] == pTable.CDF() );
            CHECK( refTables[ pIndex ][ 1 ] == pTable.totalXS() );
            CHECK( refTables[ pIndex ][ 2 ] == pTable.elasticXS() );
            CHECK( refTables[ pIndex ][ 3 ] == pTable.fissionXS() );
            CHECK( refTables[ pIndex ][ 4 ] == pTable.captureXS() );
            CHECK( refTables[ pIndex ][ 5 ] == pTable.heating() );

            pIndex = 1;
            pTable = UNR.probabilityTables()[ pIndex ];
            CHECK( refTables[ pIndex ][ 0 ] == pTable.CDF() );
            CHECK( refTables[ pIndex ][ 1 ] == pTable.totalXS() );
            CHECK( refTables[ pIndex ][ 2 ] == pTable.elasticXS() );
            CHECK( refTables[ pIndex ][ 3 ] == pTable.fissionXS() );
            CHECK( refTables[ pIndex ][ 4 ] == pTable.captureXS() );
            CHECK( refTables[ pIndex ][ 5 ] == pTable.heating() );

            pIndex = 2;
            pTable = UNR.probabilityTables()[ pIndex ];
            CHECK( refTables[ pIndex ][ 0 ] == pTable.CDF() );
            CHECK( refTables[ pIndex ][ 1 ] == pTable.totalXS() );
            CHECK( refTables[ pIndex ][ 2 ] == pTable.elasticXS() );
            CHECK( refTables[ pIndex ][ 3 ] == pTable.fissionXS() );
            CHECK( refTables[ pIndex ][ 4 ] == pTable.captureXS() );
            CHECK( refTables[ pIndex ][ 5 ] == pTable.heating() );
          } // THEN
        } // WHEN
      }
    }
  } // GIVEN valid

  GIVEN( "invalid input parameters" ){
    WHEN( "INTT is invalid" ){
      std::vector< int > invalidINTT{ 1, 3, 4, 6 };
      for( auto intt: invalidINTT ){
        THEN( "INTT = " + std::to_string( intt ) + "an exception is thrown" ){
          CHECK_THROWS(
              ContinuousEnergyNeutron::UnresolvedResonanceRange( 
                  intt, ILF, IOA, IFF, energies, ptables )
              );
        }
      }
    }
    WHEN( "IFF is invalid" ){
      std::vector< int > invalidIFF{ -1, 2 };
      for( auto iff: invalidIFF ){
        THEN( "IFF = " + std::to_string( iff ) + "an exception is thrown" ){
          CHECK_THROWS(
              ContinuousEnergyNeutron::UnresolvedResonanceRange( 
                  INTT, ILF, IOA, iff, energies, ptables )
              );
        }
      }
    }
    WHEN( "energies are negative" ){
      std::vector< double > energies{ 1.0, -2.0, 3.2 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          ContinuousEnergyNeutron::UnresolvedResonanceRange( 
              INTT, ILF, IOA, IFF, energies, ptables ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
  } // GIVEN invalid
} // SCENARIO
