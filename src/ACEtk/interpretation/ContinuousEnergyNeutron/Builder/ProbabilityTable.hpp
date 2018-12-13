struct ProbabilityTable{

  int interpolationParameter;
  int inelasticCompetition;
  int otherAbsorption;
  Factors factors;
  details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > incidentEnergies;
  details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > CDFs;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder.hpp"
};
