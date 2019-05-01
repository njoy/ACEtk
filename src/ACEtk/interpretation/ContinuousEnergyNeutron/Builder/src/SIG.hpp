template< typename R1, typename R2,
          utility::Require< true, utility::is_range, R1 > = true,
          utility::Require< true, utility::is_range, R2 > = true
        >
void SIG(int jxsIndex, R1&& npReactions, R2&& nonnpReactions ){

  auto NMT = npReactions.size() + nonnpReactions.size();

  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& jxs = tData.JXS();

  // LSIG Block
  auto LOCA_i = xss.size() + 1;
  jxs[ jxsIndex ] = LOCA_i;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );

  auto jxs7 = LOCA_i + NMT;
  jxs[ jxsIndex + 1 ] = jxs7;

  auto ACEifyReactionList = [&]( auto& reactions ) -> void {
    auto XS = reactions
      | ranges::view::transform( 
          []( auto& reaction ) { return reaction.second.crossSection; } );

    for( decltype( auto ) crossSection : XS ){
      xss[ LOCA_i - 1 ] = xss.size() - jxs7 + 2;

      details::ACEify( tData, crossSection );
      LOCA_i +=1;
    }
  };

  ACEifyReactionList( npReactions );
  ACEifyReactionList( nonnpReactions );
}
