template< typename = int >
void ACEify( Table::Data& tData, double& LOCB ) {
  // njoy::Log::info( "AngularDistribution ACEify." );
  
  LOCB = 1;

  auto& grid = this->energyGrid;
  auto& xss = tData.XSS();

  auto jxsRelative = tData.JXS( 9 );

  xss.push_back( grid.size() );
  xss |= ranges::action::push_back( this->energyGrid );
  auto LXS = xss.size() + 1;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, grid.size() ) );

  auto enumerated = ranges::view::enumerate( this->representations );
  for( auto it = enumerated.begin(); it != enumerated.end(); ++it ){
    decltype( auto ) index = std::get< 0 >( *it );
    decltype( auto ) distribution = std::get< 1 >( *it );

    double LC{0};
    details::ACEify( tData, distribution, LC );

    xss[ jxsRelative + LXS + index - 1 ] = LC;
  }
}
