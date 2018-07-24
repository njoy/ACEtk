#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;
using namespace dimwits;

SCENARIO( "Constructing a tabulated representation of fission multiplicity" ){
  std::vector< double > regions{ 3, 4, 6 };
  std::vector< double > iSchemes{ 1, 2, 3 };
  std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
  std::vector< double > multiplicities{ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
    
  GIVEN( "valid pieces of a Tabulated nubar" ){
    WHEN( "a Tabulated is constructed" ){
      ContinuousEnergyNeutron::fissionMultiplicity::Tabulated tabulated(
         regions, iSchemes,
         energies, multiplicities );

      THEN( "the contents can be verified" ){

        std::vector< double > Es{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
        auto refEnergies = scaleBy( 
            1.0*mega( electronVolts ) )( Es );
        njoy::Log::info( "refEnergies.size: {}", refEnergies.size() );
        for( const auto pair : ranges::view::zip( refEnergies, tabulated.energies() ) ){
          REQUIRE( pair.first == pair.second );
        }

        for( const auto pair : ranges::view::zip( 
                multiplicities, tabulated.multiplicities() ) ){
          REQUIRE( pair.first == Approx( pair.second ) );
        }

        AND_THEN( "the 'regions' can be verified (twice)" ){
          // Once
          for( const auto pair : ranges::view::zip
                                 ( ranges::view::iota( 0ul, regions.size() ),
                                   tabulated.regions() ) ){
            auto NBT = regions[ pair.first ];
            auto eRange = pair.second.first;

            REQUIRE( NBT == eRange.end() - energies.begin() );
          }

          // Twice
          auto refEnergies2 = energies 
            | ranges::view::take( int( regions[ 0 ] ) );
          auto trialEnergies = tabulated.regions()[ 0 ].first;
          REQUIRE( ranges::equal( refEnergies2, trialEnergies ) );

          auto refMultiplicities = multiplicities 
            | ranges::view::take( int( regions[ 0 ] ) );
          auto trialMultiplicities = tabulated.regions()[ 0 ].second;
          REQUIRE( ranges::equal( refMultiplicities, trialMultiplicities ) );

          for( size_t i=1; i < regions.size(); i++ ){
            auto refEnergies2 = energies 
              | ranges::view::take( int( regions[ i ] ) )
              | ranges::view::drop_exactly( int( regions[ i-1 ]-1 ) );
            auto trialEnergies = tabulated.regions()[ i ].first;
            REQUIRE( ranges::equal( refEnergies2, trialEnergies ) );

            auto refMultiplicities2 = multiplicities 
              | ranges::view::take( int( regions[ i ] ) )
              | ranges::view::drop_exactly( int( regions[ i-1 ]-1 ) );
            auto trialMultiplicities = tabulated.regions()[ i ].second;
            REQUIRE( ranges::equal( refMultiplicities2, trialMultiplicities ) );
          }
        }

        for( const auto pair : ranges::view::zip(
                iSchemes, tabulated.interpolationParameters().schemes() ) ){
          REQUIRE( pair.first == Approx( pair.second ) );
        }
      }
    }
    
    WHEN( "a Tabulated is constructed without interpolation parameters" ){
      std::vector< double > regions;
      std::vector< double > iSchemes;
      ContinuousEnergyNeutron::fissionMultiplicity::Tabulated tabulated(
         regions, iSchemes, energies, multiplicities );

      THEN( "the contents can be verified" ){

        std::vector< double > Es{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
        auto refEnergies = scaleBy( 
            1.0*mega( electronVolts ) )( Es );
        for( const auto pair : 
             ranges::view::zip( refEnergies, tabulated.energies() ) ){
          REQUIRE( pair.first == pair.second );
        }

        for( const auto pair : ranges::view::zip( 
                multiplicities, tabulated.multiplicities() ) ){
          REQUIRE( pair.first == Approx( pair.second ) );
        }

        REQUIRE( 0 == tabulated.interpolationParameters().size() );
      }
    }
  } // GIVEN

  GIVEN( "invalid pieces of a Tabulated nubar" ){
    WHEN( "energies size != multiplicities size" ){
      std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0 };

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS_AS( 
          ContinuousEnergyNeutron::fissionMultiplicity::Tabulated(
            regions, iSchemes, energies, multiplicities ),
          std::range_error
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0, 4.1 };

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS_AS( 
          ContinuousEnergyNeutron::fissionMultiplicity::Tabulated(
            regions, iSchemes, energies, multiplicities ),
          details::verify::exceptions::Unsorted
        );
      }
    }
    WHEN( "energies are not positive" ){
      std::vector< double > energies{ -1.0, 2.0, 3.0, 4.0, 5.0, 5.0 };

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS_AS( 
          ContinuousEnergyNeutron::fissionMultiplicity::Tabulated(
            regions, iSchemes, energies, multiplicities ),
          details::verify::exceptions::NotPositive
        );
      }
    }
    WHEN( "multiplicies are not positive" ){
      std::vector< double > multiplicities{ -1.0, 2.0, 3.0, 4.0, 5.0, 5.0 };

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS_AS( 
          ContinuousEnergyNeutron::fissionMultiplicity::Tabulated(
            regions, iSchemes, energies, multiplicities ),
          details::verify::exceptions::NotPositive
        );
      }
    }
  } // GIVEN
} // SCENARIO

