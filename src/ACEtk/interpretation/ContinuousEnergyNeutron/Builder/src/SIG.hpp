template< typename R1, typename R2,
          utility::Require< true, utility::is_range, R1 > = true,
          utility::Require< true, utility::is_range, R2 > = true
        >
void SIG(int indexJXS, R1&& npReactions, R2&& nonnpReactions ){

  auto npSize = npReactions.size();
  auto nnpSize = nonnpReactions.size();
  auto NMT = npSize + nnpSize;

  auto getXS = []( auto& reaction ) -> auto&
  { return reaction.second.crossSection; };

  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& jxs = tData.JXS();

  // LSIG Block
  auto LXS = xss.size() + 1;
  jxs[ indexJXS ] = LXS;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );
  LXS += NMT;

  // Neutron producing reactions
  auto npEnumerated = npReactions
    | ranges::view::transform( getXS )
    | ranges::view::enumerate;
  jxs[ indexJXS + 1 ] = xss.size() + 1;
  for( auto it = npEnumerated.begin(); it != npEnumerated.end(); ++it ){

    auto index = std::get< 0 >( *it );
    auto crossSection = std::get< 1 >( *it );
    xss[ LXS + index - 1 ] = xss.size() - LXS + 2;

    details::ACEify( tData, crossSection );

  }
  // non neutron producing reactions
  auto nnpEnumerated = nonnpReactions
    | ranges::view::transform( getXS )
    | ranges::view::enumerate;

  jxs[ indexJXS + 1 ] = xss.size() + 1;
  for( auto it = nnpEnumerated.begin(); it != nnpEnumerated.end(); ++it ){

    auto index = std::get< 0 >( *it );
    auto crossSection = std::get< 1 >( *it );
    xss[ LXS + index - 1 ] = xss.size() - LXS + 2;

    details::ACEify( tData, crossSection );

  }
}
