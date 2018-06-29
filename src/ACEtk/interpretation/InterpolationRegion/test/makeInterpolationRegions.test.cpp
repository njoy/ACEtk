#include "catch.hpp"

#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "making regions" ){
  std::vector< double > INT{ 2, 3 };
  std::vector< double > NBT{ 3, 5 };
  std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0 };
  std::vector< double > nubar { 0.1, 0.2, 0.3, 0.4, 0.5 };

  GIVEN( "valid input values" ){
    ENDFInterpolationParameters eip{ NBT, INT };

    auto regions = makeInterpolationRegions( eip.range(), energies, nubar );

    THEN( "the output can be verified" ){
      auto slicer = ranges::view::slice( 0, 3 );
      REQUIRE( 2 == regions[ 0 ].interpolationScheme() );
      REQUIRE( ranges::equal( energies | slicer, regions[ 0 ].x() ) );
      REQUIRE( ranges::equal( nubar | slicer, regions[ 0 ].y() ) );

      slicer = ranges::view::slice( 2, 5 );
      REQUIRE( 3 == regions[1].interpolationScheme() );
      REQUIRE( ranges::equal( energies | slicer, regions[ 1 ].x() ) );
      REQUIRE( ranges::equal( nubar | slicer, regions[ 1 ].y() ) );
    }
  }
} // SCENARIO
