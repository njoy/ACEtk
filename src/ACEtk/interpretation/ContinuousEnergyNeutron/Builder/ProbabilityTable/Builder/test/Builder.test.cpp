#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing Builder::ProbabilityTable::Builder" ){
  ContinuousEnergyNeutron::Builder parentBuilder{};
  using PTBuilder = decltype( parentBuilder.probabilityTable() );

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
          .table()
            .CDFs( njoy::utility::copy( CDFs ) )
            .totalCrossSections( njoy::utility::copy( totalXS ) )
            .elasticCrossSections( njoy::utility::copy( elasticXS ) )
            .fissionCrossSections( njoy::utility::copy( fissionXS ) )
            .captureCrossSections( njoy::utility::copy( captureXS ) )
            .heating( njoy::utility::copy( heating ) )
          .add()
          .table()
            .CDFs( njoy::utility::copy( CDFs ) )
            .totalCrossSections( njoy::utility::copy( totalXS ) )
            .elasticCrossSections( njoy::utility::copy( elasticXS ) )
            .fissionCrossSections( njoy::utility::copy( fissionXS ) )
            .captureCrossSections( njoy::utility::copy( captureXS ) )
            .heating( njoy::utility::copy( heating ) )
          .add();

        auto pTable = tb.construct();

        THEN( "the values can be verified" ){
          CHECK( INT == pTable.interpolationParameter );
          CHECK( inelasticCompetition == pTable.inelasticCompetition );
          CHECK( otherAbsorption == pTable.otherAbsorption );
          CHECK( factors == pTable.factors );
          CHECK( ranges::equal( energies, pTable.incidentEnergies ) );

          AND_THEN( "the contents can be ACE-ified" ){
            std::vector< double > aceified{};
            aceified.push_back( 3 );
            aceified.push_back( 2 );
            aceified.push_back( INT );
            aceified.push_back( inelasticCompetition );
            aceified.push_back( otherAbsorption );
            aceified.push_back( static_cast< int > ( factors ) );
            aceified |= ranges::action::push_back( energies );
            aceified |= ranges::action::push_back( CDFs );
            aceified |= ranges::action::push_back( totalXS );
            aceified |= ranges::action::push_back( elasticXS );
            aceified |= ranges::action::push_back( fissionXS );
            aceified |= ranges::action::push_back( captureXS );
            aceified |= ranges::action::push_back( heating );
            aceified |= ranges::action::push_back( CDFs );
            aceified |= ranges::action::push_back( totalXS );
            aceified |= ranges::action::push_back( elasticXS );
            aceified |= ranges::action::push_back( fissionXS );
            aceified |= ranges::action::push_back( captureXS );
            aceified |= ranges::action::push_back( heating );

            Table::Data data{};
            pTable.ACEify( data );

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
          .table()
            .CDFs( njoy::utility::copy( CDFs ) )
            .totalCrossSections( njoy::utility::copy( totalXS ) )
            .elasticCrossSections( njoy::utility::copy( elasticXS ) )
            .captureCrossSections( njoy::utility::copy( captureXS ) )
          .add()
          .table()
            .CDFs( njoy::utility::copy( CDFs ) )
            .totalCrossSections( njoy::utility::copy( totalXS ) )
            .elasticCrossSections( njoy::utility::copy( elasticXS ) )
            .captureCrossSections( njoy::utility::copy( captureXS ) )
          .add()
          .table()
            .CDFs( njoy::utility::copy( CDFs ) )
            .totalCrossSections( njoy::utility::copy( totalXS ) )
            .elasticCrossSections( njoy::utility::copy( elasticXS ) )
            .captureCrossSections( njoy::utility::copy( captureXS ) )
          .add();

        auto pTable = tb.construct();

        THEN( "the values can be verified" ){
          CHECK( INT == pTable.interpolationParameter );
          CHECK( inelasticCompetition == pTable.inelasticCompetition );
          CHECK( otherAbsorption == pTable.otherAbsorption );
          CHECK( factors == pTable.factors );
          CHECK( ranges::equal( energies, pTable.incidentEnergies ) );
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
  }
} // SCENARIO
