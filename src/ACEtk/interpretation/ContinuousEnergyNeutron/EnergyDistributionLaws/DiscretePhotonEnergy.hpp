class DiscretePhotonEnergy {
  int primaryFlag_;
  double photonEnergy_;
public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/DiscretePhotonEnergy/src/ctor.hpp"

  int primaryFlag() const { return primaryFlag_; }
  double photonEnergy() const { return photonEnergy_; }

};

typedef DiscretePhotonEnergy Law2;
