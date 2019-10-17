template< typename = int >
void ACEify( Table::Data& tData, double& LOCB ) {

  auto& xss = tData.XSS();
  auto jxsRelative = tData.JXS( 9 );

  LOCB = ( xss.size() - jxsRelative + 2 );
  
  auto& grid = this->energyGrid;

  xss.push_back( grid.size() );
  xss |= ranges::action::push_back( this->energyGrid );
  auto LC_i = xss.size() + 1;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, grid.size() ) );

  for( auto& distribution : this->representations ){

    double LC{0};
    details::ACEify( tData, distribution, LC );

    xss[ LC_i - 1 ] = LC;
    LC_i += 1;
  }
}
