#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("Testing JXS from el03"){
  auto table = Table( njoy::utility::slurpFileToMemory("1000.e03") );
  
  GIVEN("The JXS array for 1000.e03"){

    WHEN("querying 1st entry of JXS,"
	 "offset for line data") {
      REQUIRE( table.data.JXS(1) == 1 );
    }

    WHEN("querying 2nd entry of JXS,"
	 "offset for radiative stopping power numbers") {
      REQUIRE( table.data.JXS(2) == 3 );
    }

    WHEN("querying 3rd entry of JXS,"
	 "offset for Mott cross section corrections") {
      REQUIRE( table.data.JXS(3) == 174 );
    }

    WHEN("querying 4th entry of JXS,"
	 "offset for Riley cross section evaluation") {
      REQUIRE( table.data.JXS(4) == 282 );
    }

    WHEN("querying 5th entry of JXS,"
	 "offset for ITS3.0 bremsstrahlung production database") {
      REQUIRE( table.data.JXS(5) == 408 );
    }

    WHEN("querying 6th entry of JXS,"
	 "unused") {
      REQUIRE( table.data.JXS(6) == 0 );
    }

    WHEN("querying 7th entry of JXS,"
	 "offset for internally calculated Riley cross sections") {
      REQUIRE( table.data.JXS(7) == 0 );
    }    

    WHEN("querying 8th entry of JXS,"
	 "offset for internally calculated functions of Z") {
      REQUIRE( table.data.JXS(8) == 0 );
    }

    WHEN("querying 9th entry of JXS,"
	 "offset for photon energy ratios") {
      REQUIRE( table.data.JXS(9) == 2205 );
    }

    WHEN("querying 10th entry of JXS,"
	 "offset for photon energy ratio for angular distribution") {
      REQUIRE( table.data.JXS(10) == 2294 );
    }

    WHEN("querying 11th entry of JXS,"
	 "offsest for oscillator descriptions for density effect calculation") {
      REQUIRE( table.data.JXS(11) == 2328 );
    }
  }
}
