void ACEify( Table::Data& tData, int ){
  decltype( auto ) xss = tData.XSS();
  xss.push_back( this->interpolationParameter );
  xss.push_back( this->cosineGrid.size() );
  xss |= ranges::action::push_back( cosineGrid );
  xss |= ranges::action::push_back( pdf );
  xss |= ranges::action::push_back( cdf );
}
