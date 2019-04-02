void ACEify( Table::Data& tData, int jxsRelative ){
  auto& xss = tData.XSS();

  auto N_p = angularDistributions.size();
  xss |= ranges::action::push_back( 
    ranges::view::concat(
      ranges::view::single( interpolationParameter ),
      ranges::view::single( N_p ),
      energies, pdf, cdf
    )
  );
  // Locators
  auto L = xss.size();
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, N_p ));

  for( size_t i = 0; i < N_p; i++ ){
    // Set locator value
    auto K = xss.size();
    auto sizeDiff = K - jxsRelative;
    xss[ L + i ] = sizeDiff + 1;

    angularDistributions[ i ].ACEify( tData, jxsRelative );
  }
}

