struct DiscretePhotonEnergy {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy/Builder.hpp"

  int primaryFlag;
  double energy;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy/src/ACEify.hpp"
};
