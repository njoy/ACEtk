template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void DLW(int jxsIndex, Range&& distributions ){

  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& jxs = tData.JXS();

  auto NMT = distributions.size();

  auto LED = xss.size() + 1;
  jxs[ jxsIndex ] = LED;

  // Precursor energy distributions
  jxs[ jxsIndex + 1 ] = LED + NMT;

  this->ACEifyEDs( distributions, tData, LED, NMT );
}
