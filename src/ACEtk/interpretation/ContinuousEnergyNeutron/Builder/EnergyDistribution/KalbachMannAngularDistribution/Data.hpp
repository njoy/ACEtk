struct Data {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution.hpp"

  int interpolationParameter;
  details::verify::Sorted< 
      details::verify::Positive< std::vector< double > > > energies;
  details::verify::Positive< std::vector< double > > pdf;
  details::verify::CDF< std::vector< double > > cdf;
  std::vector< AngularDistribution > angularDistributions;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/src/ACEify.hpp"
};
