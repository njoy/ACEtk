template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void YP(int jxsIndex, Range&& reactions ){

  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  jxs[ jxsIndex ] = xss.size() + 1;

  std::set< int > MTs;
  for( decltype( auto ) ppR : reactions ){
    MTs.insert( ppR.MT );
  }

  xss.push_back( MTs.size() );
  xss |= ranges::action::push_back( MTs );
}
