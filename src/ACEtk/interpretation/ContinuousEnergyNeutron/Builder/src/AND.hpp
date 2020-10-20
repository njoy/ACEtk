template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void AND(int jxsIndex, Range&& reactions ){

  decltype( auto ) NMT = ranges::distance( reactions );

  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  // LAND Block
  decltype( auto ) LED = xss.size() + 1;
  jxs[ jxsIndex ] = LED;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );

  // AND Block
  jxs[ jxsIndex + 1 ] = xss.size() + 1;
  decltype( auto ) enumerated = ranges::view::enumerate( reactions );
  for( decltype( auto ) it = enumerated.begin(); it != enumerated.end(); ++it ){
    decltype( auto ) pair = *it;
    decltype( auto ) index = std::get< 0 >( pair );
    decltype( auto ) reac = std::get< 1 >( pair );

    double LOCB{ 0 };
    details::ACEify( tData, reac.angularDistribution, LOCB );

    xss[ LED + index - 1 ] = LOCB;
  }
}
