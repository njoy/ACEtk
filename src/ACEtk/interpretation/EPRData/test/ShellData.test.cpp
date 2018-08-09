#include "catch.hpp"
#include "ACEtk.hpp"


using namespace njoy::ACEtk;

SCENARIO( "Test interpretation::EPRdata::ShellData" ){
  auto table = Table( njoy::utility::slurpFileToMemory( "1000.14p" ) );

  GIVEN( "An ACE Table for 1000.14p" ){
    const auto eprdata = interpretation::EPRData( table );
    eprdata.shellData();
  }
}
