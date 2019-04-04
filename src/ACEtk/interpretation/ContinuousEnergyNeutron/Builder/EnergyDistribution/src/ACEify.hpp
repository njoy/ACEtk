void ACEify( Table::Data& tData, int jxsRelative ) {

  auto& xss = tData.XSS();

  xss.push_back( law2Int( law ) );

  auto IDAT = xss.size();
  xss.push_back( 0 ); // IDAT

  tab1.ACEify( tData );

  xss[ IDAT ] = xss.size() - jxsRelative;

  std::visit( 
      [&]( auto& law ){ return law.ACEify( tData, jxsRelative ); }, law );
}
