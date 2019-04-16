template< typename Range,
          utility::Require< true, utility::is_range, Range > = true
        >
void AND(int indexJXS, Range&& reactions ){

  auto NMT = ranges::distance( reactions );

  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& jxs = tData.JXS();

  // LAND Block
  auto LXS = xss.size() + 1;
  jxs[ indexJXS ] = LXS;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );
  LXS += NMT;

  auto enumerated = ranges::view::enumerate( reactions );

  // AND Block
  jxs[ indexJXS + 1 ] = xss.size() + 1;
  for( auto it = enumerated.begin(); it != enumerated.end(); ++it ){

    auto index = std::get< 0 >( *it );
    auto angularDistribution = std::get< 1 >( *it );
    xss[ LXS + index - 1 ] = xss.size() - LXS + 2;

    details::ACEify( tData, angularDistribution );

  }
}
