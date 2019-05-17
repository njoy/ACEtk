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

  int JED = LED + NMT;
  jxs[ jxsIndex + 1 ] = JED;

  // Locators
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );

  // Energy-Dependent Neutron Yields
  decltype( auto ) edNeutronYields = reactions
    | ranges::view::filter(
      []( auto&& r ) -> decltype( auto ){ return bool( r.edNeutronYields ); } );

  for( decltype( auto ) reac : edNeutronYields ){
    long long KY = xss.size() + 1;
    long long TY = KY + 101 - JED;
    reac.neutronYield = TY*
        static_cast< int >( reac.neutronYieldReferenceFrame );

    details::ACEify( tData, reac.edNeutronYields.value() );
  }

  decltype( auto ) EDs = reactions
    | ranges::view::transform(
      []( auto&& r ) -> decltype( auto ) { return r.energyDistribution; } );
  this->ACEifyEDs( EDs, tData, LED, NMT );
}
