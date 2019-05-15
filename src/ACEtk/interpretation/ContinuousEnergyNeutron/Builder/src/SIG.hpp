template< typename R1, typename R2,
          utility::Require< true, utility::is_range, R1 > = true,
          utility::Require< true, utility::is_range, R2 > = true
        >
void SIG(int jxsIndex, R1&& npReactions, R2&& nonnpReactions ){

  decltype( auto ) NMT = ranges::distance( npReactions ) + 
                         ranges::distance( nonnpReactions );

  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  // LSIG Block
  decltype( auto ) LOCA_i = xss.size() + 1;
  jxs[ jxsIndex ] = LOCA_i;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );

  decltype( auto ) jxs7 = LOCA_i + NMT;
  jxs[ jxsIndex + 1 ] = jxs7;

  decltype( auto ) ACEifyReactionList = 
      [&]( auto&& xsList ) -> void {

    for( decltype( auto ) xs : xsList ){
      xss[ LOCA_i - 1 ] = xss.size() - jxs7 + 2;

      details::ACEify( tData, xs );
      LOCA_i +=1;
    }
  };

  ACEifyReactionList( npReactions );
  ACEifyReactionList( nonnpReactions );
}
