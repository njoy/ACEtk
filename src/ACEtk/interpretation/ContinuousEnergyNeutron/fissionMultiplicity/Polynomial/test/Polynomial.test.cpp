#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO( "Constructing a polynomial representation of fission multiplicity" ){
  GIVEN( "a list of polynomial coefficients" ){
    std::vector< double > coeffs; coeffs.reserve(10);
    std::iota( coeffs.begin(), coeffs.end(), 1.0 );

    THEN( "a Polynomial can be constructed" ){
      interpretation::nc::fissionMultiplicity::Polynomial poly( coeffs );

      AND_THEN( "the coefficients can be verified" ){
        REQUIRE( ranges::equal( coeffs, poly.coefficients() ) );
      }
    }
  } // GIVEN
} // SCENARIO
