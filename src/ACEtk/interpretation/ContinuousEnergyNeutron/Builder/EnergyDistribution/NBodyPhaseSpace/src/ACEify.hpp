void ACEify( Table::Data& tData, int ){
  tData.XSS().push_back( this->numberBodies );
  tData.XSS().push_back( this->totalMassRatio );
}
