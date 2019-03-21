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

    // std::visit( nuVisitor, foundPrompt );
    auto promptSize = this->xss.size();

    if( foundTotal ){
      // std::visit( nuVisitor, foundTotal );
      auto totalSize = this->xss.size() - promptSize;
      this->xss.insert( this->xss.begin() + size, -1*totalSize );
    }
  }
  else if( foundTotal ){
    // std::visit( nuVisitor, foundTotal );
  }
  else{
    this->jxs[ 1 ] = 0;
  }

  if( not this->delayedPrecursors_.empty() ){
  }


}
