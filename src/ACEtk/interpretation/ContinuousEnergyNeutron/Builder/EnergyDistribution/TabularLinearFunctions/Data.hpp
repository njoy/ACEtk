struct Data {

  std::vector< double > P;
  std::vector< double > T;
  std::vector< double > C;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularLinearFunctions/Data/Builder.hpp"

  void ACEify( Table::Data& tData){
    tData.XSS() |= ranges::action::push_back(
        ranges::view::concat( P, T, C ) );
  }
};
