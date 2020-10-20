void GPD(){
  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) jxs = tData.JXS();

  if( not this->totalGammaProduction_ ){
    return;
  }

  decltype( auto ) tGP = this->totalGammaProduction_.value();

  jxs[ 11 ] = xss.size() + 1;
  xss |= ranges::action::push_back( tGP.crossSection );

  if( tGP.outgoingEnergies ){
    xss |= ranges::action::push_back( 
        tGP.outgoingEnergies.value() | ranges::view::join );
  }
}
