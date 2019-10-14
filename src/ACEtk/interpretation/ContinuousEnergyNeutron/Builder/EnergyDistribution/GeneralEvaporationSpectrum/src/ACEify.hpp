void ACEify( Table::Data& tData, int ){
  tabulatedEffectiveTemperature.ACEify( tData );
  tData.XSS().push_back( this->equiprobableBins.size() );
  tData.XSS() |= ranges::action::push_back( this->equiprobableBins );
}
