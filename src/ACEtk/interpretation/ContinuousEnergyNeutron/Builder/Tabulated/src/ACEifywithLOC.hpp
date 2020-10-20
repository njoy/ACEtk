void ACEifywithLOC( Table::Data& tData, int jxsRelative ){
  this->ACEifyNoty( tData );

  decltype( auto ) xss = tData.XSS();

  // Locators
  long long L = xss.size();
  long long ySize = this->y.size();
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, ySize ));

  for( long long i = 0; i < ySize; i++ ){
    // Set locator value
    long long K = xss.size();
    long long sizeDiff = K - jxsRelative;
    xss[ L + i ] = sizeDiff + 1;

    this->y[ i ].ACEify( tData, jxsRelative );
  }

}
