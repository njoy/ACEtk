/*
 * This function will ACEify a range of energy distributions. It will in turn,
 * call the ACEify function for each EnergyDistribution
 *
 * distributions: range of EnergyDistributions
 * LED: Location in XSS where locators begin
 * NMT: Number of reactions that have secondary energy distribution(s)
 */
template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void ACEifyEDs( Range&& distributions,
                Table::Data& tData, 
                int LED, int NMT ) {

  Log::info( "ACEifying EDs" );
  Log::info( "distributions size: {}", ranges::distance( distributions ) );
  decltype( auto ) xss = tData.XSS();
  // Locators
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );

  int JED = LED + NMT;

  decltype( auto ) inumerated = ranges::view::enumerate( distributions );
  for( auto it = inumerated.begin(); it != inumerated.end(); ++it ){
    decltype( auto ) pair = *it;
    decltype( auto ) index = std::get< 0 >( pair );
    decltype( auto ) ed = std::get< 1 >( pair );

    auto LOCC = static_cast< long long >( xss.size() + 1 ) - JED + 1;
    xss[ LED + index - 1 ] = LOCC;

    decltype( auto ) kt = ed.begin();
    for( ; kt != ranges::prev( ed.end() ); ++kt ){

      xss.push_back( 0 ); // LNW
      long long LNW_i = xss.size() - 1;

      details::ACEify( tData, *kt, JED );

      auto LNW = static_cast< long long >( xss.size() ) - ( JED - 1 ) + 1;
      xss[ LNW_i ] = LNW;

    } // for kndex
    xss.push_back( 0 ); // LNW
    details::ACEify( tData, *kt, JED );

  } // for index
}
