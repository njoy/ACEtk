#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO( "Constructing a tabulated representation of fission multiplicity" ){
  GIVEN( "the pieces of a TAB1 Record" ){
    std::vector< long > regions{ 4, 5, 6 };
    std::vector< long > interpolation{ 1, 2, 3 };
    std::vector< double > x{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    std::vector< double > y{ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
    
    WHEN( "a Tabulated is constructed" ){
      interpretation::nc::fissionMultiplicity::Tabulated tabulated(
          1.0, 2.0, 3, 4,
         std::move( regions ), 
         std::move( interpolation ),
         std::move( x ), std::move( y ) );

      THEN( "the contents can be verified" ){

        std::vector< double > Es{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
        auto refEnergies = scaleBy( 1.0*mega( electronVolts ) )( Es );
        njoy::Log::info( "refEnergies.size: {}", refEnergies.size() );
        for( const auto pair : ranges::view::zip( refEnergies, tabulated.energies() ) ){
          REQUIRE( pair.first == pair.second );
        }

        std::vector< double > refMultiplicities{ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
        for( const auto pair : ranges::view::zip( 
                refMultiplicities, tabulated.multiplicities() ) ){
          REQUIRE( pair.first == Approx( pair.second ) );
        }
      }
    }
  } // GIVEN
} // SCENARIO

