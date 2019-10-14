void ACEify( Table::Data& tData, int jxsRelative ){
  decltype( auto ) xss = tData.XSS();

  if( tabulated.parameters ){
    decltype( auto ) p = tabulated.parameters.value();
    xss.push_back( p.first.size() );
    xss |= ranges::action::push_back( p.first );
    xss |= ranges::action::push_back( p.second );
  }
  else{
    xss.push_back( 0 );
  }
  
  // energies
  xss.push_back( tabulated.x.size() );
  xss |= ranges::action::push_back( tabulated.x );

  // Locators
  long long L = xss.size();
  long long ySize = tabulated.y.size();
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, ySize ));

  for( long long i = 0; i < ySize; i++ ){
    // Set locator value
    long long K = xss.size();
    long long sizeDiff = K - jxsRelative;
    xss[ L + i ] = sizeDiff + 1;

    tabulated.y[ i ].ACEify( tData, jxsRelative );
  }
}
