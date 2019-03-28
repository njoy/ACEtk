void ACEify( Table::Data& tData ){
  auto& xss = tData.XSS();
  auto LDAT = xss.size();

  if( tabulated.parameters ){
    auto p = tabulated.parameters.value();
    xss 
      |= ranges::action::push_back( 
          ranges::view::concat(
            ranges::view::single( p.first.size() ), p.first, p.second
          )
        );
  }
  else{
    xss |= ranges::action::push_back( ranges::view::single( 0 ) );
  }
  
  // energies
  xss |= ranges::action::push_back(
    ranges::view::concat(
      ranges::view::single( tabulated.x.size() ),
      tabulated.x
    )
  );

  // Locators
  auto L = xss.size();
  auto ySize = tabulated.y.size();
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, ySize ));

  for( size_t i = 0; i < ySize; i++ ){
    // Set locator value
    auto K = xss.size();
    auto sizeDiff = K - LDAT;
    xss[ L + i ] = sizeDiff + 1;

    tabulated.y[ i ].ACEify( tData );
  }
}
