Builder& SZA( int sza ) {
  if( sza < 0 ){
    Log::error( "SZA must be >= 0" );
    Log::info( "Received SZA value of: {}", sza );
    throw std::exception();
  }
  this->SZA_ = sza;
  return *this;
}

Builder& ZA( int za ){
  return SZA( za );
}
