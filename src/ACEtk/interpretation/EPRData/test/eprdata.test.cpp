#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"


using namespace njoy::ACEtk;

SCENARIO( "Test interpretation::EPRdata interface" ){
  auto table = Table( njoy::utility::slurpFileToMemory( "1000.14p" ) );
  const auto eprdata = interpretation::EPRData( std::move(table) );
  REQUIRE( eprdata.atomicNumber() == 1 );
}
