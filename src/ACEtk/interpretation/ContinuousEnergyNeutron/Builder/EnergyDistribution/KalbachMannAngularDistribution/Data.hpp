struct Data {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution.hpp"

  int interpolationParameter;
  dvS< 
      dvP< std::vector< double > > > energies;
  dvP< std::vector< double > > pdf;
  dvC< std::vector< double > > cdf;
  std::vector< AngularDistribution > angularDistributions;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/src/ACEify.hpp"
};
