#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Adding probability table" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};
  // auto ptBuilder = ncBuilder.probabilityTable();

  GIVEN( "valid data" ){
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
    
    CHECK_NOTHROW(
      ncBuilder.probabilityTable()
                .interpolationParameter( INT )
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
               .add()
    );
  }
}
