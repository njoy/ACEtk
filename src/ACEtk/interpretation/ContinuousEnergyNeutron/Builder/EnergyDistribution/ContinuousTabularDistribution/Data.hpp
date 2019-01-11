struct Data{

  int interpolationParameter;
  std::vector< double > energies;
  std::vector< double > pdf;
  std::vector< double > cdf;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder.hpp"
};
