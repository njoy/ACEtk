template< typename = int >
void ACEify( Table::Data& tData, double& LOCB ) {

  auto& xss = tData.XSS();
  auto jxsRelative = tData.JXS( 9 );

  LOCB = ( xss.size() - jxsRelative + 1 );
  
  auto& grid = this->energyGrid;

  xss.push_back( grid.size() );
  xss |= ranges::action::push_back( this->energyGrid );
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, grid.size() ) );

  auto enumerated = ranges::view::enumerate( this->representations );
  for( auto it = enumerated.begin(); it != enumerated.end(); ++it ){
    decltype( auto ) index = std::get< 0 >( *it );
    decltype( auto ) distribution = std::get< 1 >( *it );

    double LC{0};
    details::ACEify( tData, distribution, LC );

    xss[ jxsRelative + index - 1 ] = LC;
  }
}
