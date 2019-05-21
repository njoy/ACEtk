template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void DLWP(int jxsIndex, Range&& reactions ){

  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  decltype( auto ) NMT = ranges::distance( reactions );

  decltype( auto ) LED = xss.size() + 1;
  jxs[ jxsIndex ] = LED;

  int JED = LED + NMT;
  jxs[ jxsIndex + 1 ] = JED;

  // Locators
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );

  decltype( auto ) EDs = reactions
    | ranges::view::transform(
      []( auto&& r ) -> decltype( auto ) { return r.energyDistribution; } );
  this->ACEifyEDs( EDs, tData, LED, NMT );
}
