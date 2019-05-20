template< typename = int >
void ACEify( Table::Data& tData, double& LOCB ) {
  auto& xss = tData.XSS();
  auto jxsRelative = tData.JXS( 17 );

  LOCB = ( xss.size() - jxsRelative + 2 );
  
  xss.push_back( this->energyGrid.size() );
  xss |= ranges::action::push_back( this->energyGrid );
  auto N_e = this->energyGrid.size();

  auto LC_i = xss.size();
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, N_e ) );
  
  for( size_t i = 0; i < N_e; ++i ){
    double LC{ 0 };
    decltype( auto ) ad = this->cosineBins[ i ];

    if( ad ){
      LC = xss.size() - jxsRelative + 2;
      xss |= ranges::action::push_back( ad.value() );
    }
    xss[ LC_i ] = LC;

    LC_i += 1;
  }
}
