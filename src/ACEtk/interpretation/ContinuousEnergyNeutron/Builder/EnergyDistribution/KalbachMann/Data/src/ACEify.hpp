void ACEify( Table::Data& tData, int ){
  decltype( auto ) xss = tData.XSS();
  xss.push_back( this->interpolationParameter );
  xss.push_back( this->energies.size() );
  xss |= ranges::action::push_back( this->energies );
  xss |= ranges::action::push_back( this->pdf );
  xss |= ranges::action::push_back( this->cdf );
  xss |= ranges::action::push_back( this->precompoundFraction );
  xss |= ranges::action::push_back( this->angularDistributionSlope );
}
