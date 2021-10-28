#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/DosimetryTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

std::string chunk();
void verifyChunk( const Table& );

SCENARIO( "DosimetryTable" ){

  GIVEN( "An ACE Table for 13027.24y" ) {

    auto ACETable = Table( njoy::utility::slurpFileToMemory("13027.24y") );
    WHEN( "constructing a DosimetryTable" ){

      const auto ncTable = DosimetryTable( std::move( ACETable ) );

      THEN( "parameters can be extracted" ){

        CHECK( "13027.24y" == ncTable.ZAID() );
        CHECK( 0. == Approx( ncTable.temperature() ) );

        CHECK( 1165 == ncTable.length() );
        CHECK( 13027 == ncTable.ZA() );
        CHECK( 2 == ncTable.NTR() );
        CHECK( 2 == ncTable.numberReactions() );

        // MTR block
        CHECK( false == ncTable.MTR().empty() );
        CHECK( 2 == ncTable.MTR().MTs().size() );
        CHECK( 103 == ncTable.MTR().MTs().front() );
        CHECK( 107 == ncTable.MTR().MTs().back() );
        CHECK( 2 == ncTable.MTR().reactionNumbers().size() );
        CHECK( 103 == ncTable.MTR().reactionNumbers().front() );
        CHECK( 107 == ncTable.MTR().reactionNumbers().back() );

        CHECK( 103 == ncTable.MTR().MT( 1 ) );
        CHECK( 107 == ncTable.MTR().MT( 2 ) );
        CHECK( 103 == ncTable.MTR().reactionNumber( 1 ) );
        CHECK( 107 == ncTable.MTR().reactionNumber( 2 ) );

        CHECK( true == ncTable.MTR().hasReactionNumber( 103 ) );
        CHECK( true == ncTable.MTR().hasReactionNumber( 107 ) );
        CHECK( 1 == ncTable.MTR().index( 103 ) );
        CHECK( 2 == ncTable.MTR().index( 107 ) );

        // SIGD block
        CHECK( false == ncTable.SIG().empty() );
        CHECK( 2 == ncTable.SIG().NTR() );

        CHECK( 1 == ncTable.SIG().LSIG( 1 ) );
        CHECK( 615 == ncTable.SIG().LSIG( 2 ) );

      }
    }
  }
}
