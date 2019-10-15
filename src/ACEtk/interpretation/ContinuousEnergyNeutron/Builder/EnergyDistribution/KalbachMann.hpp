struct KalbachMann {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data.hpp"

  Tabulated< Data > tabulated;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Builder.hpp"

  void ACEify( Table::Data& tData, int jxsRelative ){
    this->tabulated.ACEifywithLOC( tData, jxsRelative );
  }
};
