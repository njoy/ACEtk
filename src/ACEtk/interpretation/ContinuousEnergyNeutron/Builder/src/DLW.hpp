template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void DLW(int jxsIndex, Range&& reactions ){

  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  decltype( auto ) NMT = reactions.size();

  decltype( auto ) LED = xss.size() + 1;
  jxs[ jxsIndex ] = LED;

  jxs[ jxsIndex + 1 ] = LED + NMT;

  // Locators
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );

  decltype( auto ) EDs = reactions
    | ranges::view::transform(
      []( auto&& r ) -> decltype( auto ) { return r.energyDistribution; } );
  this->ACEifyEDs( EDs, tData, LED, NMT );
}
