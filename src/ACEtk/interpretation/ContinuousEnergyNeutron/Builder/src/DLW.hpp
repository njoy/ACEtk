template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void DLW(int jxsIndex, Range&& distributions ){

  Log::info( "DLW" );
  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  decltype( auto ) NMT = distributions.size();

  decltype( auto ) LED = xss.size() + 1;
  jxs[ jxsIndex ] = LED;

  // Precursor energy distributions
  jxs[ jxsIndex + 1 ] = LED + NMT;

  this->ACEifyEDs( distributions, tData, LED, NMT );
}
