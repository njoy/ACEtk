void ACEify( Table::Data& tData, int JED ) {

  decltype( auto ) xss = tData.XSS();

  xss.push_back( law2Int( law ) );

  decltype( auto ) IDAT_i = xss.size();
  xss.push_back( 0 ); // IDAT

  details::ACEify( tData, tab1 );

  xss[ IDAT_i ] = xss.size() - ( JED - 1 ) + 1;

  std::visit( 
    [&]( auto&& law ) -> decltype( auto )
      { return details::ACEify( tData, law, JED ); }, 
    law );
}
