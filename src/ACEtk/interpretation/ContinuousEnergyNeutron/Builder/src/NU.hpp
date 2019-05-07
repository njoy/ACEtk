void NU(){
  decltype( auto ) foundPrompt = (
      fissionMultiplicity_.find( "prompt" ) != fissionMultiplicity_.end() );
  decltype( auto ) foundTotal = (
      fissionMultiplicity_.find( "total" ) != fissionMultiplicity_.end() );

  decltype( auto ) tData = this->tableData_.value();
  decltype( auto ) xss = tData.XSS();
  decltype( auto ) nxs = tData.NXS();
  decltype( auto ) jxs = tData.JXS();

  decltype( auto ) nuVisitor = 
    [&](auto& nubar ) -> void { nubar.ACEify( tData ); };

  decltype( auto ) size = xss.size() + 1;
  jxs[ 1 ] = size;
  if( foundPrompt ){
    decltype( auto ) prompt = this->fissionMultiplicity_[ "prompt" ];

    std::visit( nuVisitor, prompt );
    decltype( auto ) promptSize = xss.size();

    if( foundTotal ){
      decltype( auto ) total = this->fissionMultiplicity_[ "total" ];

      std::visit( nuVisitor, total );

      decltype( auto ) totalSize = xss.size() - promptSize;
      xss.insert( xss.begin() + size, -1*totalSize );
    }
  }
  else if( foundTotal ){
      decltype( auto ) total = this->fissionMultiplicity_[ "total" ];
      std::visit( nuVisitor, total );
  }
  else{
    jxs[ 1 ] = 0;
  }

  decltype( auto ) NPCR = this->delayedPrecursors_.size();
  if( NPCR ){
    nxs[ 7 ] = NPCR;
    jxs[ 23 ] = xss.size() + 1;

    // ACEify precursors
    for( decltype( auto ) pre : this->delayedPrecursors_ ){
      pre.ACEify( tData );

    }

    // ACEify precursor energy distributions
    decltype( auto ) LED = xss.size() + 1;
    jxs[ 25 ] = LED;

    // Precursor energy distributions
    decltype( auto ) EDs = this->delayedPrecursors_
      | ranges::view::transform(
        []( auto&& dp ) -> decltype( auto ){ return dp.energyDistribution; }
      );
    decltype( auto ) NMT = EDs.size();
    nxs[ 7 ] = NMT;
    jxs[ 26 ] = LED + NMT;

    this->ACEifyEDs( EDs, tData, LED, NMT );
  }
}
