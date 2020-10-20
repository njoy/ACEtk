void ACEify( Table::Data& tData, int jxsRelative ){
  decltype( auto ) xss = tData.XSS();

  long long NMU = energyDistributions.size();
  xss.push_back( this->interpolationParameter );
  xss.push_back( NMU );
  xss |= ranges::action::push_back( cosines );

  long long L = xss.size();
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMU ) );

  long long K = xss.size();
  for( long long i = 0; i < NMU; i++ ){
    K = xss.size();
    long long sizeDiff = K - jxsRelative;
    xss[ L + i ] = sizeDiff + 1;

    energyDistributions[ i ].ACEify( tData, jxsRelative );
  }

}
