template< typename R1, typename R2,
          utility::Require< true, utility::is_range, R1 > = true,
          utility::Require< true, utility::is_range, R2 > = true
        >
void LQR(int indexJXS, R1&& npReactions, R2&& nonnpReactions ){
  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& jxs = tData.JXS();

  auto SLQR = xss.size() + 1;
  jxs[ indexJXS ] = xss.size() + 1;

  for( const auto& reac : npReactions ){ xss.push_back( reac.second.Q ); }
  for( const auto& reac : nonnpReactions ){ xss.push_back( reac.second.Q ); }

}
