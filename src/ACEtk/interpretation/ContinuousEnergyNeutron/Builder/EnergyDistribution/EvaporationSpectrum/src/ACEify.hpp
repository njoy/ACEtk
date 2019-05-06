void ACEify( Table::Data& tData, int ){
  tabulatedEffectiveTemperature.ACEify( tData );
  tData.XSS().push_back( restrictionEnergy );
}
