struct ProbabilityTable{

  int interpolationParameter;
  int inelasticCompetition;
  int otherAbsorption;
  Factors factors;
  details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > incidentEnergies;
  details::verify::CDF< std::vector< double > > CDFs;
  details::verify::Positive< std::vector< double > > totalCrossSections;
  details::verify::Positive< std::vector< double > > elasticCrossSections;
  details::verify::Positive< std::vector< double > > fissionCrossSections;
  details::verify::Positive< std::vector< double > > captureCrossSections;
  details::verify::Positive< std::vector< double > > heating;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder.hpp"
};
