#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "fissionMultiplicity components ofContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};

  WHEN( "valid strings for nuType are used" ){
    std::vector< std::string > validnuTypes{ "total", "prompt", "delayed" };
    
    for( auto nuType : validnuTypes ){
      GIVEN( "polynomial fission multiplicity parameters: " + nuType ){
        std::vector< double > coefficients{ 1.0, 2.0, 5.0, 6.0 };

        if( nuType != "delayed" ){
          CHECK_NOTHROW( 
            ncBuilder.fissionMultiplicity( nuType )
                    .polynomial()
                    .coefficients( std::move( coefficients ) )
                    .add()
          );
        }
        if( nuType == "delayed" ){
          CHECK_THROWS( ncBuilder.fissionMultiplicity( nuType ) .polynomial() );
        }
      }
      GIVEN( "tabulated fission multiplicity parameters: " + nuType ){
        std::vector< int > boundaries{ 1, 3 };
        std::vector< int > schemes{ 2, 1 };
        std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
        std::vector< double > multiplicities{ 2.1, 2.2, 2.5, 2.5 };
        CHECK_NOTHROW( 
          ncBuilder.fissionMultiplicity( nuType )
                   .tabulated()
                      .boundaries( std::move( boundaries ) )
                      .schemes( std::move( schemes ) )
                      .energies( std::move( energies ) )
                      .multiplicities( std::move( multiplicities ) )
                   .add()
        );
      }
    }
  }
  WHEN( "invalid strings are used to create a fissionMultiplicity::Builder" ){
    std::vector< std::string > invalidnuTypes{ "abc", "prompts", "both" };

    for( auto nuType : invalidnuTypes ){
      THEN ( "an exception is thrown when nuType = " + nuType ){
        CHECK_THROWS_AS( 
          ncBuilder.fissionMultiplicity( nuType ),
          std::range_error&
        );
      }
    }
  }
} // SCENARIO

