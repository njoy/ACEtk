#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Constructing coupled density functions" ){
  GIVEN( "valid PDF and CDF" ){
    std::vector< double > PDF{ 0.1, 0.2, 0.3, 0.3, 0.1 };
    std::vector< double > CDF{ 0.1, 0.3, 0.6, 0.9, 1.0 };

    WHEN( "the coupled density function is constructed" ){
      CoupledDensityFunctions pdf_cdf( PDF, CDF );

      THEN( "the values can be verified" ){
        REQUIRE( 5 == pdf_cdf.PDF().size() );
        REQUIRE( 5 == pdf_cdf.CDF().size() );
        REQUIRE( ranges::equal( PDF, pdf_cdf.PDF() ) );
        REQUIRE( ranges::equal( CDF, pdf_cdf.CDF() ) );
      }
    }
  } // GIVEN

  GIVEN( "invalid PDF or CDF" ){

    WHEN( "PDF and CDF are not of the same length" ){
      std::vector< double > PDF{ 0.1, 0.2, 0.3, 0.3 };
      std::vector< double > CDF{ 0.1, 0.3, 0.6, 0.9, 1.0 };

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( CoupledDensityFunctions( PDF, CDF ) );
      }

    }
  }
} // SCENARIO
