struct Data{

  int interpolationParameter;
  dvS< 
      dvP< std::vector< double > > > energies;
  dvP< std::vector< double > > pdf;
  dvC< std::vector< double > > cdf;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/src/ACEify.hpp"
};
