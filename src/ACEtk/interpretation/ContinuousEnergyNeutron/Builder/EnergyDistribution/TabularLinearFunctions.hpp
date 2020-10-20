struct TabularLinearFunctions {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Data.hpp"

  Tabulated< Data > tabulated;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Builder.hpp"

  void ACEify( Table::Data& tData, int jxsRelative ){
    this->tabulated.ACEifywithLOC( tData, jxsRelative );
  }
};
