Builder& comment( std::string c ){
  try{ 
    this->comments_.emplace_back( c );
  } catch( std::exception& ){
    Log::info( "Header comment size must be <= 70" );
    Log::info( "Received comment of size: {}", c.size() );
    throw;
  }
  return *this;
}
