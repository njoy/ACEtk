void ACEify( Table::Data& tData, int jxsRelative ) {

  auto& xss = tData.XSS();

  xss.push_back( law2Int( law ) );

  auto IDAT = xss.size();
  Log::info( "IDAT: {}", IDAT );
  xss.push_back( 0 ); // IDAT

  tab1.ACEify( tData );

  auto diff = xss.size() - IDAT + 2;
  xss[ IDAT ] = diff + 1;

  std::visit( 
      [&]( auto& law ){ return law.ACEify( tData, jxsRelative ); }, law );
}
