void ACEify( Table::Data& tData, int ){
  this->aTabulated.ACEify( tData );
  this->bTabulated.ACEify( tData );
  tData.XSS() |= ranges::action::push_back( 
      ranges::view::single( this->restrictionEnergy ) );
}
