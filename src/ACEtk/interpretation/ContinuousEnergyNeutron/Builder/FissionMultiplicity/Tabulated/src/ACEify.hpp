void ACEify( Table::Data& tData ){
  auto& xss = tData.XSS();

  xss.push_back( 2 );
  Tabulated1D::ACEify( tData );
}
