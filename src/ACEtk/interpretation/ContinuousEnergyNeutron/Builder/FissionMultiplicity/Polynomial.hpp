struct Polynomial{

  std::vector< double > coefficients;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Polynomial/Builder.hpp"

  void ACEify( Table::Data& tData){
    decltype( auto ) xss = tData.XSS();
    xss.push_back( 1 );
    xss |= ranges::action::push_back( this->coefficients );
  }
};
