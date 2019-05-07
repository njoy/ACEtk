void ACEify( Table::Data& tData ){
  decltype( auto ) xss = tData.XSS();
  xss |= ranges::action::push_back( this->P );
  xss |= ranges::action::push_back( this->T );
  xss |= ranges::action::push_back( this->C );
}
