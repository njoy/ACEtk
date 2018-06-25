class NbodyPhaseSpace {
  int numberBodies_;
  double totalMassRatio_;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/EnergyDistributionLaws/NbodyPhaseSpace/src/ctor.hpp"

  int numberBodies() const { return numberBodies_; }
  int NPSX() const { return numberBodies_; }
  double totalMassRatio() const { return totalMassRatio_; }
  double Ap() const { return totalMassRatio_; }
};

typedef NbodyPhaseSpace Law66;
