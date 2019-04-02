void ACEify( Table::Data& tData, int jxsRelative ) {

  auto& xss = tData.XSS();

  xss.push_back( law2Int( law ) );
  xss.push_back( jxsRelative - xss.size () ); // IDAT

  tab1.ACEify( tData );
  std::visit( 
      [&]( auto& law ){ return law.ACEify( tData, jxsRelative ); }, law );
}
