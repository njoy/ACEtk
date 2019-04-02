void ACEify( Table::Data& tData, int jxsRelative ){
  auto& xss = tData.XSS();

  auto NMU = energyDistributions.size();
  xss |= ranges::action::push_back(
    ranges::view::concat(
        ranges::view::single( interpolationParameter ),
        ranges::view::single( NMU ),
        cosines
    )
  );

  auto L = xss.size();
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMU ) );

  auto K = xss.size();
  for( size_t i = 0; i < NMU; i++ ){
    K = xss.size();
    auto sizeDiff = K - jxsRelative;
    xss[ L + i ] = sizeDiff + 1;

    energyDistributions[ i ].ACEify( tData, jxsRelative );
  }

}
