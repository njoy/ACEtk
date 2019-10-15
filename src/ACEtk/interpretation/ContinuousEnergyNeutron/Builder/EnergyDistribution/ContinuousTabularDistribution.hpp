struct ContinuousTabularDistribution {
  
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data.hpp"

  Tabulated< Data > tabulated;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Builder.hpp"

  void ACEify( Table::Data& tData, int jxsRelative ){
    this->tabulated.ACEifywithLOC( tData, jxsRelative );
  }
};
