template< typename = int >
void ACEify( Table::Data& tData, int jxsRelative ) {

  auto& grid = this->energyGrid;
  auto& xss = tData.XSS();

  Log::info( "# distributions: {}", grid.size() );
  xss.push_back( grid.size() );
  xss |= ranges::action::push_back( this->energyGrid );
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, grid.size() ) );

  auto enumerated = ranges::view::enumerate( this->representations );
  for( auto it = enumerated.begin(); it != enumerated.end(); ++it ){
    auto index = std::get< 0 >( *it );
    decltype( auto ) distribution = std::get< 1 >( *it );

    Log::info( "index: {}", index );

    auto LC_i = jxsRelative + index - 1;
    Log::info( "LC_i: {}", LC_i );

    auto& LC = xss[ jxsRelative + index - 1 ];
    // static_assert( details::hasACEify< decltype( distribution ), double& >::value, "barf" );

    details::ACEify( tData, distribution, LC );
    auto distance = xss.size() - ( jxsRelative - 1 ) + 1;
    Log::info( "distance: {}", distance );
    Log::info( "LC: {}", LC );
    LC = LC*distance;
    Log::info( "LC*distance: {}", LC );
  }
}
