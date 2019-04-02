struct LevelScattering {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering/Builder.hpp"

  double atomicWeightRatio;
  double QValue;

  void ACEify( Table::Data& tData, int ){
    tData.XSS().push_back( QValue );
    tData.XSS().push_back( atomicWeightRatio );
  }
};
