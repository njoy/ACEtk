template< typename R1, typename R2,
          utility::Require< true, utility::is_range, R1 > = true,
          utility::Require< true, utility::is_range, R2 > = true
        >
void TYR(int indexJXS, R1&& npReactions, R2&& nonnpReactions ){
  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  jxs[ indexJXS ] = xss.size() + 1;

  decltype( auto ) getReac = []( auto&& p ){ return p.second; };

  for( decltype( auto ) reac : 
      npReactions | ranges::view::transform( getReac ) ){ 
    xss.push_back( reac.neutronYield*
                   static_cast< int >( reac.neutronYieldReferenceFrame ) );
  }
  for( decltype( auto ) reac : 
      nonnpReactions | ranges::view::transform( getReac ) ){ 
    xss.push_back( reac.neutronYield );
  }
}
