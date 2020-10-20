void ACEify( Table::Data& tData, int ){
  tData.XSS().push_back( primaryFlag );
  tData.XSS().push_back( energy );
}
