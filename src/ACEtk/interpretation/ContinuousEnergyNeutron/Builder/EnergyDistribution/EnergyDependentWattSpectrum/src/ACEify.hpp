void ACEify( Table::Data& tData ){
  aTabulated.ACEify( tData );
  bTabulated.ACEify( tData );
  tData.XSS() |= ranges::action::push_back( 
      ranges::view::single( restrictionEnergy ) );
}
