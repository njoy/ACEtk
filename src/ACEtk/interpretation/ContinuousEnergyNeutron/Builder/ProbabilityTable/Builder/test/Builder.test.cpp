#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing Builder::ProbabilityTable::Builder" ){
  ContinuousEnergyNeutron::Builder parentBuilder{};
  using PTBuilder = decltype( 
      parentBuilder.probabilityTable() );

  struct TestBuilder : public PTBuilder {
    using PTBuilder::construct;
    using PTBuilder::PTBuilder;
  };

  TestBuilder tb{ parentBuilder };

  int INT{ 2 };
  int inelasticCompetition{ 3 };
  int otherAbsorption{ 54 };
  ContinuousEnergyNeutron::Builder::Factors factors{ 
    ContinuousEnergyNeutron::Builder::Factors::CROSSSECTIONS };
  std::vector< double > energies{ 1.0, 2.0, 3.0 };
  std::vector< double > CDFs{ 0.1, 0.4, 1.0 };
  std::vector< double > totalXS{ 10, 20, 30 };
  std::vector< double > elasticXS{ 11, 21, 31 };
  std::vector< double > fissionXS{ 12, 22, 32 };
  std::vector< double > captureXS{ 13, 23, 33 };
  std::vector< double > heating{ 14, 24, 34 };

  GIVEN( "valid inputs" ){
    std::vector< int > validINTs{ 2, 5 };
    for( auto INT : validINTs ){
      WHEN( "building a probability table with interpolation parameter: " 
            + std::to_string( INT ) ){

        tb.interpolationParameter( INT )
          .inelasticCompetition( inelasticCompetition )
          .otherAbsorption( otherAbsorption )
          .factors( factors )
          .incidentEnergies( njoy::utility::copy( energies ) )
          .CDFs( njoy::utility::copy( CDFs ) )
          .totalCrossSections( njoy::utility::copy( totalXS ) )
          .elasticCrossSections( njoy::utility::copy( elasticXS ) )
          .fissionCrossSections( njoy::utility::copy( fissionXS ) )
          .captureCrossSections( njoy::utility::copy( captureXS ) )
          .heating( njoy::utility::copy( heating ) );
        auto pTable = tb.construct();

        THEN( "the values can be verified" ){
          CHECK( INT == pTable.interpolationParameter );
          CHECK( inelasticCompetition == pTable.inelasticCompetition );
          CHECK( otherAbsorption == pTable.otherAbsorption );
          CHECK( factors == pTable.factors );
          CHECK( ranges::equal( energies, pTable.incidentEnergies ) );
          CHECK( ranges::equal( CDFs, pTable.CDFs ) );
          CHECK( ranges::equal( totalXS, pTable.totalCrossSections ) );
          CHECK( ranges::equal( elasticXS, pTable.elasticCrossSections ) );
          CHECK( ranges::equal( fissionXS, pTable.fissionCrossSections ) );
          CHECK( ranges::equal( captureXS, pTable.captureCrossSections ) );
          CHECK( ranges::equal( heating, pTable.heating ) );

          AND_THEN( "the contents can be ACE-ified" ){
            std::vector< double > aceified{};
            aceified |= ranges::action::push_back( CDFs );
            aceified |= ranges::action::push_back( totalXS );
            aceified |= ranges::action::push_back( elasticXS );
            aceified |= ranges::action::push_back( fissionXS );
            aceified |= ranges::action::push_back( captureXS );
            aceified |= ranges::action::push_back( heating );

            Table::Data data{};
            pTable.ACEify( data );

            njoy::Log::info( "aceified: {}", aceified | ranges::view::all );
            njoy::Log::info( "data.XSS: {}", data.XSS() | ranges::view::all );
            CHECK( ranges::equal( aceified, data.XSS() ) );
          }
        }
      }
    }
    WHEN( "adding probability table without heating or fission values" ){
        tb.interpolationParameter( INT )
          .inelasticCompetition( inelasticCompetition )
          .otherAbsorption( otherAbsorption )
          .factors( factors )
          .incidentEnergies( njoy::utility::copy( energies ) )
          .CDFs( njoy::utility::copy( CDFs ) )
          .totalCrossSections( njoy::utility::copy( totalXS ) )
          .elasticCrossSections( njoy::utility::copy( elasticXS ) )
          .captureCrossSections( njoy::utility::copy( captureXS ) );
        auto pTable = tb.construct();

        THEN( "the values can be verified" ){
          CHECK( INT == pTable.interpolationParameter );
          CHECK( inelasticCompetition == pTable.inelasticCompetition );
          CHECK( otherAbsorption == pTable.otherAbsorption );
          CHECK( factors == pTable.factors );
          CHECK( ranges::equal( energies, pTable.incidentEnergies ) );
          CHECK( ranges::equal( CDFs, pTable.CDFs ) );
          CHECK( ranges::equal( totalXS, pTable.totalCrossSections ) );
          CHECK( ranges::equal( elasticXS, pTable.elasticCrossSections ) );
          CHECK( ranges::equal( { 0.0, 0.0, 0.0 }, 
                                pTable.fissionCrossSections ) );
          CHECK( ranges::equal( captureXS, pTable.captureCrossSections ) );
          CHECK( ranges::equal( { 0.0, 0.0, 0.0 }, pTable.heating ) );
        }
    }
  } // GIVEN
  GIVEN( "invalid inputs" ){
    WHEN( "incident energies are not all positive" ){
      std::vector< double > energies{ 1.0, -2.0, 3.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.incidentEnergies( energies ),
            details::verify::exceptions::NotPositive& 
        );
      }
    }
    WHEN( "incident energies are not sorted" ){
      std::vector< double > energies{ 1.0, 4.0, 3.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.incidentEnergies( energies ),
            details::verify::exceptions::Unsorted& 
        );
      }
    }
    WHEN( "CDFs are not all positive" ){
      std::vector< double > CDFs{ 0.1, -2.0, 1.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.CDFs( CDFs ),
            details::verify::exceptions::InvalidCDF& 
        );
      }
    }
    WHEN( "CDFs are not sorted" ){
      std::vector< double > CDFs{ 0.2, 0.1, 1.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.CDFs( CDFs ),
            details::verify::exceptions::InvalidCDF& 
        );
      }
    }
    WHEN( "CDFs are not the same size as incident energies" ){
      std::vector< double > CDFs{ 0.1, 0.4, 0.6, 1.0 };
      tb.interpolationParameter( INT )
        .inelasticCompetition( inelasticCompetition )
        .otherAbsorption( otherAbsorption )
        .factors( factors )
        .incidentEnergies( njoy::utility::copy( energies ) )
        .CDFs( njoy::utility::copy( CDFs ) )
        .totalCrossSections( njoy::utility::copy( totalXS ) )
        .elasticCrossSections( njoy::utility::copy( elasticXS ) )
        .fissionCrossSections( njoy::utility::copy( fissionXS ) )
        .captureCrossSections( njoy::utility::copy( captureXS ) )
        .heating( njoy::utility::copy( heating ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.construct(),
            std::range_error&
        );
      }
    }
    WHEN( "total cross section is not all positive" ){
      std::vector< double > totalXS{ 0.1, -2.0, 1.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.totalCrossSections( totalXS ),
            details::verify::exceptions::NotPositive& 
        );
      }
    }
    WHEN( "total cross section is not the same size as incident energies" ){
      std::vector< double > totalXS{ 0.1, 0.4, 0.6, 1.0 };
      tb.interpolationParameter( INT )
        .inelasticCompetition( inelasticCompetition )
        .otherAbsorption( otherAbsorption )
        .factors( factors )
        .incidentEnergies( njoy::utility::copy( energies ) )
        .CDFs( njoy::utility::copy( CDFs ) )
        .totalCrossSections( njoy::utility::copy( totalXS ) )
        .elasticCrossSections( njoy::utility::copy( elasticXS ) )
        .fissionCrossSections( njoy::utility::copy( fissionXS ) )
        .captureCrossSections( njoy::utility::copy( captureXS ) )
        .heating( njoy::utility::copy( heating ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.construct(),
            std::range_error&
        );
      }
    }
    WHEN( "elastic cross section is not all positive" ){
      std::vector< double > elasticXS{ 0.1, -2.0, 1.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.elasticCrossSections( elasticXS ),
            details::verify::exceptions::NotPositive& 
        );
      }
    }
    WHEN( "elastic cross section is not the same size as incident energies" ){
      std::vector< double > elasticXS{ 0.1, 0.4, 0.6, 1.0 };
      tb.interpolationParameter( INT )
        .inelasticCompetition( inelasticCompetition )
        .otherAbsorption( otherAbsorption )
        .factors( factors )
        .incidentEnergies( njoy::utility::copy( energies ) )
        .CDFs( njoy::utility::copy( CDFs ) )
        .totalCrossSections( njoy::utility::copy( totalXS ) )
        .elasticCrossSections( njoy::utility::copy( elasticXS ) )
        .fissionCrossSections( njoy::utility::copy( fissionXS ) )
        .captureCrossSections( njoy::utility::copy( captureXS ) )
        .heating( njoy::utility::copy( heating ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.construct(),
            std::range_error&
        );
      }
    }
    WHEN( "fission cross section is not all positive" ){
      std::vector< double > fissionXS{ 0.1, -2.0, 1.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.fissionCrossSections( fissionXS ),
            details::verify::exceptions::NotPositive& 
        );
      }
    }
    WHEN( "fission cross section is not the same size as incident energies" ){
      std::vector< double > fissionXS{ 0.1, 0.4, 0.6, 1.0 };
      tb.interpolationParameter( INT )
        .inelasticCompetition( inelasticCompetition )
        .otherAbsorption( otherAbsorption )
        .factors( factors )
        .incidentEnergies( njoy::utility::copy( energies ) )
        .CDFs( njoy::utility::copy( CDFs ) )
        .totalCrossSections( njoy::utility::copy( totalXS ) )
        .elasticCrossSections( njoy::utility::copy( elasticXS ) )
        .fissionCrossSections( njoy::utility::copy( fissionXS ) )
        .captureCrossSections( njoy::utility::copy( captureXS ) )
        .heating( njoy::utility::copy( heating ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.construct(),
            std::range_error&
        );
      }
    }
    WHEN( "capture cross section is not all positive" ){
      std::vector< double > captureXS{ 0.1, -2.0, 1.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.captureCrossSections( captureXS ),
            details::verify::exceptions::NotPositive& 
        );
      }
    }
    WHEN( "capture cross section is not the same size as incident energies" ){
      std::vector< double > captureXS{ 0.1, 0.4, 0.6, 1.0 };
      tb.interpolationParameter( INT )
        .inelasticCompetition( inelasticCompetition )
        .otherAbsorption( otherAbsorption )
        .factors( factors )
        .incidentEnergies( njoy::utility::copy( energies ) )
        .CDFs( njoy::utility::copy( CDFs ) )
        .totalCrossSections( njoy::utility::copy( totalXS ) )
        .elasticCrossSections( njoy::utility::copy( elasticXS ) )
        .fissionCrossSections( njoy::utility::copy( fissionXS ) )
        .captureCrossSections( njoy::utility::copy( captureXS ) )
        .heating( njoy::utility::copy( heating ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.construct(),
            std::range_error&
        );
      }
    }
    WHEN( "heating is not all positive" ){
      std::vector< double > heating{ 0.1, -2.0, 1.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.heating( heating ),
            details::verify::exceptions::NotPositive& 
        );
      }
    }
    WHEN( "heating is not the same size as incident energies" ){
      std::vector< double > heating{ 0.1, 0.4, 0.6, 1.0 };
      tb.interpolationParameter( INT )
        .inelasticCompetition( inelasticCompetition )
        .otherAbsorption( otherAbsorption )
        .factors( factors )
        .incidentEnergies( njoy::utility::copy( energies ) )
        .CDFs( njoy::utility::copy( CDFs ) )
        .totalCrossSections( njoy::utility::copy( totalXS ) )
        .elasticCrossSections( njoy::utility::copy( elasticXS ) )
        .fissionCrossSections( njoy::utility::copy( fissionXS ) )
        .captureCrossSections( njoy::utility::copy( captureXS ) )
        .heating( njoy::utility::copy( heating ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
            tb.construct(),
            std::range_error&
        );
      }
    }
  }
} // SCENARIO
