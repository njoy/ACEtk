void ACEify( Table::Data& tData, int){
  decltype( auto ) xss = tData.XSS();
  xss.push_back( 10*this->numberDiscretePhotonLines + 
                    this->interpolationParameter );
  xss.push_back( this->energies.size() );
  xss |= ranges::action::push_back( energies );
  xss |= ranges::action::push_back( pdf );
  xss |= ranges::action::push_back( cdf );
}
