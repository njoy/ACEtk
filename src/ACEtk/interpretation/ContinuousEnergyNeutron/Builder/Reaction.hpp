struct Reaction{
  class Builder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/CrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder.hpp"

  int MT;
  double Q;
  int neutronYield;
  Table::Slice energyGrid;
  ContinuousEnergyNeutron::Builder::CrossSection crossSection;
  AngularDistribution angularDistribution;
  EnergyDistribution energyDistribution;
};
