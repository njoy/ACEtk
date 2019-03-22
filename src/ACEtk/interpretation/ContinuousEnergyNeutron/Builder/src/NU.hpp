void NU(){
  auto foundPrompt = (
      fissionMultiplicity_.find( "prompt" ) != fissionMultiplicity_.end() );
  auto foundTotal = (
      fissionMultiplicity_.find( "total" ) != fissionMultiplicity_.end() );

  auto nuVisitor = [&](auto& nubar ) -> void
  {
    xss |= ranges::action::push_back( nubar.ACEify() );
  };

  auto size = this->xss.size() + 1;
  this->jxs[ 1 ] = size;
  if( foundPrompt ){
    auto prompt = this->fissionMultiplicity_[ "prompt" ];

    std::visit( nuVisitor, prompt );
    auto promptSize = this->xss.size();

    if( foundTotal ){
      auto total = this->fissionMultiplicity_[ "total" ];
      std::visit( nuVisitor, total );
      auto totalSize = this->xss.size() - promptSize;
      this->xss.insert( this->xss.begin() + size, -1*totalSize );
    }
  }
  else if( foundTotal ){
      auto total = this->fissionMultiplicity_[ "total" ];
      std::visit( nuVisitor, total );
  }
  else{
    this->jxs[ 1 ] = 0;
  }

  if( not this->delayedPrecursors_.empty() ){
  }
}
