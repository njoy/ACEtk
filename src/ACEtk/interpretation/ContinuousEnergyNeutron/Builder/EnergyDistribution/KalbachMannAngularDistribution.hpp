struct KalbachMannAngularDistribution {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data.hpp"

  Tabulated< Data > tabulated;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Builder.hpp"

  void ACEify( Table::Data& tData, int jxsRelative ){
    this->tabulated.ACEifywithLOC( tData, jxsRelative );
  }
};
