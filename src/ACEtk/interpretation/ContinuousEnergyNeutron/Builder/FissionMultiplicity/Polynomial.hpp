struct Polynomial{

  std::vector< double > coefficients;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Polynomial/Builder.hpp"

  void ACEify( Table::Data& tData){
    tData.XSS()
      |= ranges::action::push_back(
        ranges::view::concat( ranges::view::single( 1 ), this->coefficients ) );
  }
};
