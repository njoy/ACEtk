#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing FissionMultiplicity::Tabulated::Builder" ){
  std::string nuType{ "delayed" };
  ContinuousEnergyNeutron::Builder grandparentBuilder{};
  using ParentBuilder = decltype( 
      grandparentBuilder.fissionMultiplicity( nuType ) );
  ParentBuilder parentBuilder{ grandparentBuilder, nuType };

  using TabulatedBuilder = decltype( parentBuilder.tabulated( ) );

  struct TestBuilder : TabulatedBuilder{
    using TabulatedBuilder::construct;
    using TabulatedBuilder::TabulatedBuilder;
  };

  TestBuilder tb{ grandparentBuilder, nuType };

  std::vector< int > boundaries{ 1, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > multiplicities{ 2.1, 2.2, 2.5, 2.5 };

  GIVEN( "valid data" ){
    WHEN( "creating a Tabulated fission multiplicity with boundaries" ){
      tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .multiplicities( njoy::utility::copy( multiplicities ) );
      auto tabu = tb.construct();
      tb.add();

      THEN( "the members of Tabulated can be verified" ){
        CHECK( energies == tabu.x );
        CHECK( multiplicities == tabu.y );

        AND_THEN( "the contents can be ACE-ified" ){
          std::vector< double > aceified{};
          aceified.push_back( 2 ); // LNU
          aceified.push_back( 2 ); // N_R
          aceified |= ranges::action::push_back( boundaries ); // NBT
          aceified |= ranges::action::push_back( schemes ); // INT
          aceified.push_back( energies.size() ); // N_E
          aceified |= ranges::action::push_back( energies ); // E
          aceified |= ranges::action::push_back( multiplicities ); // nubar

          Table::Data data{};
          tabu.ACEify( data );
          CHECK( ranges::equal( aceified, data.XSS() ) );
        }
      }
    }
    WHEN( "creating a Tabulated fission multiplicity without boundaries" ){
      tb.energies( njoy::utility::copy( energies ) )
        .multiplicities( njoy::utility::copy( multiplicities ) );
      auto tabu = tb.construct();
      tb.add();

      THEN( "the members of Tabulated can be verified" ){
        CHECK( energies == tabu.x );
        CHECK( multiplicities == tabu.y );

        AND_THEN( "the contents can be ACE-ified" ){
          std::vector< double > aceified{};
          aceified.push_back( 2 ); // LNU
          aceified.push_back( 0 ); // N_R
          aceified.push_back( energies.size() ); // N_E
          aceified |= ranges::action::push_back( energies ); // E
          aceified |= ranges::action::push_back( multiplicities ); // nubar

          Table::Data data{};
          tabu.ACEify( data );
          CHECK( ranges::equal( aceified, data.XSS() ) );
        }
      }
    }
  } // GIVEN valid
  GIVEN( "invalid data" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "constructing a Tabulated fission multiplicity "
          "without all it's components" ){
      CHECK_THROWS( tb.construct() );

      THEN( "an exception is thrown" ){
        tb.energies( njoy::utility::copy( energies ) );
        CHECK_THROWS( tb.construct() );
      }
      THEN( "an exception is thrown" ){
        tb.multiplicities( njoy::utility::copy( multiplicities ) );
        CHECK_THROWS( tb.construct() );
      }
    }
  } // GIVEN
} // SCENARIO
