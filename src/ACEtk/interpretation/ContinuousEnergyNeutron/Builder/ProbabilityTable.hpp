struct ProbabilityTable{

  int interpolationParameter;
  int inelasticCompetition;
  int otherAbsorption;
  Factors factors;
  dvP< dvS< std::vector< double > > > incidentEnergies;
  dvC< std::vector< double > > CDFs;
  dvP< std::vector< double > > totalCrossSections;
  dvP< std::vector< double > > elasticCrossSections;
  dvP< std::vector< double > > fissionCrossSections;
  dvP< std::vector< double > > captureCrossSections;
  dvP< std::vector< double > > heating;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Builder.hpp"
};
