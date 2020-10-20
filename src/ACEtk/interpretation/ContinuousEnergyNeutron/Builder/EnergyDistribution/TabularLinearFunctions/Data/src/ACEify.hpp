void ACEify( Table::Data& tData, int ){
  decltype( auto ) xss = tData.XSS();
  xss.push_back( this->P.size() );
  xss |= ranges::action::push_back( this->P );
  xss |= ranges::action::push_back( this->T );
  xss |= ranges::action::push_back( this->C );
}
