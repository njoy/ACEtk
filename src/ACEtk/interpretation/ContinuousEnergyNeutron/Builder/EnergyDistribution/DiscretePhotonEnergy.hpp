struct DiscretePhotonEnergy {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy/Builder.hpp"

  int primaryFlag;
  double energy;

  void ACEify( Table::Data& tData ){
    tData.XSS().push_back( primaryFlag );
    tData.XSS().push_back( energy );
  }
};
