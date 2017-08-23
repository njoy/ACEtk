#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("Testing NXS from el03"){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.e03") );
  
  GIVEN("The NXS array for 1000.e03"){

    WHEN("querying 1st entry of NXS,"
	 "length of xss") {
      REQUIRE( table.data.NXS(1) == 2329 );
      REQUIRE( table.data.NXS(1) == table.data.XSS().size() );
    }

    WHEN("querying 2nd entry of NXS," 
	 "atomic number)"){
      REQUIRE( table.data.NXS(2) == 1 );
    }

    WHEN("querying 3rd entry of NXS,"
	 "number of radiation stopping power interpolation points"){
      REQUIRE( table.data.NXS(3) == 57 );
    }

    WHEN("querying 4th entry of NXS,"
	 "number of mott scattering angle cross section corrections"){
      REQUIRE( table.data.NXS(4) == 18 );
    }

    WHEN("querying 5th entry of NXS,"
	 "number of electron energy points for bremsstrahlung interpolation"){
      REQUIRE( table.data.NXS(5) == 57 );      
    }            

    WHEN("querying 6th entry of NXS,"
	 "number of photon ratio points for bremsstrahlung interpolation"){
      REQUIRE( table.data.NXS(6) == 30 );
    }

    WHEN("querying 7th entry of NXS,"
	 "unused"){
      REQUIRE( table.data.NXS(7) == 0 );
    }

    WHEN("querying 8th entry of NXS,"
	 "unused"){
      REQUIRE( table.data.NXS(8) == 0 );
    }

    WHEN("querying 9th entry of NXS,"
	 "number of interpolation points in the bremsstrahlung database for bremsstrahlung spectrum calculation"){
      REQUIRE( table.data.NXS(9) == 89 );
    }

    WHEN("querying 10th entry of NXS,"
	 "number of interpolation points in the bremsstrahlung database for angular/energy calculation"){
      REQUIRE( table.data.NXS(10) == 34 );
    }

    WHEN("querying 11th entry of NXS,"
	 "number of oscillator points for density effect calculation"){
      REQUIRE( table.data.NXS(11) == 1 );
    } 

    WHEN("querying 12th entry of NXS,"
	 "unused"){
      REQUIRE( table.data.NXS(12) == 0 );
    }

    WHEN("querying 13th entry of NXS,"
	 "unused"){
      REQUIRE( table.data.NXS(13) == 0 );
    }

    WHEN("querying 14th entry of NXS,"
	 "unused"){
      REQUIRE( table.data.NXS(14) == 0 );
    }

    WHEN("querying 15th entry of NXS,"
	 "unused"){
      REQUIRE( table.data.NXS(15) == 0 );
    }

    WHEN("querying 16th entry of NXS,"
	 "version of data"){
      REQUIRE( table.data.NXS(16) == 3 );
    }                        
    
  }
}
