struct ProbabilityTable{

  class Builder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table.hpp"

  int interpolationParameter;
  int inelasticCompetition;
  int otherAbsorption;
  Factors factors;
  dvP< dvS< std::vector< double > > > incidentEnergies;

  std::vector< Table > tables;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/src/ACEify.hpp"
};
