struct AngularDistribution {

  int interpolationParameter;
  dvCB< std::vector< double > > cosineGrid;
  dvP< std::vector< double > > pdf;
  dvC< std::vector< double > > cdf;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/AngularDistribution/src/ACEify.hpp"
};
