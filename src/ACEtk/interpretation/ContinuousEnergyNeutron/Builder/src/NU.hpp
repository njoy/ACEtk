void NU(){
  auto foundPrompt = (
      fissionMultiplicity_.find( "prompt" ) != fissionMultiplicity_.end() );
  auto foundTotal = (
      fissionMultiplicity_.find( "total" ) != fissionMultiplicity_.end() );

  auto& tData = this->tableData_.value();
  auto& xss = tData.XSS();
  auto& nxs = tData.NXS();
  auto& jxs = tData.JXS();

  auto nuVisitor = [&](auto& nubar ) -> void { nubar.ACEify( tData ); };

  auto size = xss.size() + 1;
  jxs[ 1 ] = size;
  if( foundPrompt ){
    auto prompt = this->fissionMultiplicity_[ "prompt" ];

    std::visit( nuVisitor, prompt );
    auto promptSize = xss.size();

    if( foundTotal ){
      auto total = this->fissionMultiplicity_[ "total" ];

      std::visit( nuVisitor, total );

      auto totalSize = xss.size() - promptSize;
      xss.insert( xss.begin() + size, -1*totalSize );
    }
  }
  else if( foundTotal ){
      auto total = this->fissionMultiplicity_[ "total" ];
      std::visit( nuVisitor, total );
  }
  else{
    jxs[ 1 ] = 0;
  }

  auto NPCR = this->delayedPrecursors_.size();
  if( NPCR ){
    nxs[ 7 ] = NPCR;
    jxs[ 23 ] = xss.size() + 1;

    // ACEify precursors
    for( auto& pre : this->delayedPrecursors_ ){
      pre.ACEify( tData );

    }

    // ACEify precursor energy distributions
    auto LED = xss.size() + 1;
    jxs[ 25 ] = LED;

    // Precursor energy distributions
    auto EDs = this->delayedPrecursors_
      | ranges::view::transform(
        [](auto& dp ){ return dp.energyDistribution; }
      );
    auto NMT = EDs.size();
    nxs[ 7 ] = NMT;
    jxs[ 26 ] = LED + NMT;

    this->ACEifyEDs( EDs, tData, LED, NMT );
  }
}
