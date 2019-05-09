template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true
        >
void SIGP( int jxsIndex, Range&& ppReactions ){
  decltype( auto ) NMT = ppReactions.size();

  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  // LSIGP Block
  decltype( auto ) LOCA_i = xss.size() + 1;
  jxs[ jxsIndex ] = LOCA_i;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );

  decltype( auto ) jxs15 = LOCA_i + NMT;
  jxs[ jxsIndex + 1 ] = jxs15;

  for( decltype( auto ) reac : ppReactions ){
    xss[ LOCA_i - 1 ] = xss.size() - jxs15 + 2;

    details::ACEify( tData, reac.second.crossSection );
    LOCA_i +=1;
  }

}
