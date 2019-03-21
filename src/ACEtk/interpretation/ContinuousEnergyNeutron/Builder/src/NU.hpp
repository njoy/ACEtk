void NU(){
  auto foundPrompt = (
      fissionMultiplicity_.find( "prompt" ) != fissionMultiplicity_.end() );
  auto foundTotal = (
      fissionMultiplicity_.find( "total" ) != fissionMultiplicity_.end() );

  if( foundPrompt or foundTotal ){
    this->jxs[ 1 ] = this->xss.size() + 1;
  }

  if( not this->delayedPrecursors_.empty() ){
  }


}
