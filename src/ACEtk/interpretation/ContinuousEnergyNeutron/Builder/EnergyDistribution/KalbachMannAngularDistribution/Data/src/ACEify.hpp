void ACEify( Table::Data& tData, int jxsRelative ){
  decltype( auto ) xss = tData.XSS();

  long long N_p = angularDistributions.size();
  xss.push_back( this->interpolationParameter );
  xss.push_back(N_p );
  xss |= ranges::action::push_back( energies );
  xss |= ranges::action::push_back( pdf );
  xss |= ranges::action::push_back( cdf );
  // Locators
  long long L = xss.size();
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, N_p ));

  long long K = xss.size();
  for( long long i = 0; i < N_p; i++ ){
    // Set locator value
    K = xss.size();
    long long sizeDiff = K - jxsRelative;
    xss[ L + i ] = sizeDiff + 1;

    angularDistributions[ i ].ACEify( tData, jxsRelative );
  }
}

