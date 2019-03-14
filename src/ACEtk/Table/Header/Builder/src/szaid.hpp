Builder& szaid( std::string z ){
  try{ 
    this->szaid_ = z;
  } catch( std::exception& ){
    Log::info( "(S)ZAID size must be <= 24" );
    Log::info( "Received (S)ZAID of size: {}", z.size() );
    throw;
  }
  return *this;
}

Builder& zaid( std::string z ){
  return szaid( z );
}
