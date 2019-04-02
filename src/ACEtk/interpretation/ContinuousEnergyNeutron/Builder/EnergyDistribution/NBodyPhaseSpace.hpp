struct NBodyPhaseSpace {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/NBodyPhaseSpace/Builder.hpp"

  int numberBodies;
  double totalMassRatio;

  void ACEify( Table::Data& tData, int ){
    tData.XSS().push_back( this->numberBodies );
    tData.XSS().push_back( this->totalMassRatio );
  }
};
