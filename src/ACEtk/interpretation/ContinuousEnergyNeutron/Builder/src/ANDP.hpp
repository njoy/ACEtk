template< typename R1, typename R2,
          utility::Require< true, utility::is_range, R1 > = true,
          utility::Require< true, utility::is_range, R2 > = true
        >
void ANDP(int jxsIndex, R1&& npPP, R2&& nonnpPP ){

  decltype( auto ) NMT = ranges::distance( npPP ) + 
                         ranges::distance( nonnpPP );

  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  // LSIG Block
  decltype( auto ) LOCB_i = xss.size() + 1;
  jxs[ jxsIndex ] = LOCB_i;
  xss |= ranges::action::push_back( ranges::view::repeat_n( 0, NMT ) );

  decltype( auto ) jxs17 = LOCB_i + NMT;
  jxs[ jxsIndex + 1 ] = jxs17;

  decltype( auto ) ACEifyPPAngularDistributionList = 
    [&]( auto&& adList ) ->void{

    for( decltype( auto ) ad : adList ){
      double LOCB{ 0 };
      details::ACEify( tData, ad, LOCB );

      xss[ LOCB_i - 1 ] = LOCB;
      LOCB_i += 1;
    }
  };

  ACEifyPPAngularDistributionList( npPP );
  ACEifyPPAngularDistributionList( nonnpPP );
  
}

