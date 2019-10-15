struct Data {
  int interpolationParameter;
  int numberDiscretePhotonLines;
  dvP< dvS< std::vector< double > > > energies;
  dvP< std::vector< double > > pdf;
  dvC< std::vector< double > > cdf;
  std::vector< double > precompoundFraction;
  std::vector< double > angularDistributionSlope;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/src/ACEify.hpp"
};
