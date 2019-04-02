void ACEify( Table::Data& tData, int ){
  tabulatedEffectiveTemperature.ACEify( tData );
  tData.XSS() |= ranges::action::push_back( 
      ranges::view::single( restrictionEnergy ) );
}
