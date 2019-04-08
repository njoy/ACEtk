void ACEify( Table::Data& tData, int JED ) {

  auto& xss = tData.XSS();

  xss.push_back( law2Int( law ) );

  auto IDAT_i = xss.size();
  xss.push_back( 0 ); // IDAT

  tab1.ACEify( tData );

  xss[ IDAT_i ] = xss.size() - ( JED - 1 ) + 1;

  std::visit( [&]( auto& law ){ return law.ACEify( tData, JED ); }, law );
}
