template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void TYR(int indexJXS, Range& reactions ){
  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& jxs = tData.JXS();

  jxs[ indexJXS ] = xss.size() + 1;

  for( const auto& reac : reactions ){

    xss.push_back( reac.second.neutronYield );

  }
}