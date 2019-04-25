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
  auto LXS = xss.size();
  auto LOCA_i = LXS;
  jxs[ jxsIndex ] = LOCA_i;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );

  auto jxs7 = xss.size();
  jxs[ jxsIndex + 1 ] = jxs7;

  auto ACEifyReactionList = [&]( auto& reactions ) -> void {
    auto XS = reactions
      | ranges::view::transform( 
          []( auto& reaction ) { return reaction.second.crossSection; } );
    auto enumeratedXS = XS | ranges::view::enumerate;

    double LOCA{ 0 };
    for( decltype( auto ) crossSection : XS ){
      LOCA = xss.size() - jxs7 + 1;
      xss[ LOCA_i -1 ] = xss.size() - jxs7 + 1;

      details::ACEify( tData, crossSection );
      LOCA_i +=1;
    }
  };

  ACEifyReactionList( npReactions );
  ACEifyReactionList( nonnpReactions );
}
