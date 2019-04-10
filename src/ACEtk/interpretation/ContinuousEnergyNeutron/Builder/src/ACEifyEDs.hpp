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
void ACEifyEDs( Range& distributions,
                Table::Data& tData, 
                int LED, int NMT ) {


  auto& xss = tData.XSS();
  // Locators
  xss |= ranges::action::push_back( 
    ranges::view::repeat_n( 0, NMT )
  );

  auto JED = LED + NMT;

  auto N = distributions.size();
  int LOCC{ 0 };
  for( size_t index = 0; index < N; index++ ){

    LOCC = ( xss.size() + 1 ) - JED + 1;
    xss[ LED + index - 1 ] = LOCC;

    auto ed = distributions[ index ];
    int LNW_i{ 0 };
    int LNW{ 0 };

    for( size_t kndex = 0; kndex < ed.size(); kndex++ ){
      xss.push_back( 0 ); // LNW
      LNW_i = xss.size() - 1;

      ed[ kndex ].ACEify( tData, JED );

      if( kndex != ( ed.size() - 1 ) ){
        LNW = xss.size() - ( JED - 1 ) + 1;
        xss[ LNW_i ] = LNW;
      } // if
    } // for kndex

  } // for index
}
