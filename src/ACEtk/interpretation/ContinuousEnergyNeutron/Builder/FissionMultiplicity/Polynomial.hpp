struct Polynomial{

  std::vector< double > coefficients;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Polynomial/Builder.hpp"

  void ACEify( Table::Data& tData){
    decltype( auto ) xss = tData.XSS();
    xss.push_back( 1 );
    xss.push_back( this->coefficients.size() );
    xss |= ranges::action::push_back( this->coefficients );
  }
};
