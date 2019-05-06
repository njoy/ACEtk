void ACEify( Table::Data& tData, int ){
  this->aTabulated.ACEify( tData );
  this->bTabulated.ACEify( tData );
  tData.XSS().push_back( restrictionEnergy );
}
