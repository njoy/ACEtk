/*
 * This function will ACEify a range of energy distributions. It will in turn,
 * call the ACEify function for each EnergyDistribution
 *
 * distributions: range of EnergyDistributions
 * LED: Location in XSS where locators begin
 * JED: Location in XSS where EnergyDistributions begin
 */
template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void ACEifyEDs( Range& distributions,
                Table::Data& tData, 
                int LED, int JED ) {


  auto& xss = tData.XSS();

  auto N = distributions.size();
  int LOCC{ 0 };
  for( size_t index = 0; index < N; index++ ){
    LOCC = xss.size() - JED;
    xss[ LED + index ] = LOCC;

    auto ed = distributions[ index ];
    int LNW{ 0 };

    for( size_t kndex = 0; kndex < ed.size(); kndex++ ){
      xss.push_back( 0 ); // LNW
      LNW = xss.size();

      ed[ kndex ].ACEify( tData, JED );

      if( kndex != ( ed.size() - 1 ) ){
        xss[ LNW ] = xss.size() + 1;
      } // if
    } // for
  } // for
}
