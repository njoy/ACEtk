template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void MTRP(int indexJXS, Range&& reactions ){
  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  jxs[ indexJXS ] = xss.size() + 1;
  for( decltype( auto ) reac : reactions ){ xss.push_back( reac.first ); }
}
