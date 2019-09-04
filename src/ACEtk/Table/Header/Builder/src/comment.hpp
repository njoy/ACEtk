Builder& comment( const std::string& c ){
  try{ 
    this->comments_.emplace_back( c );
  } catch( std::exception& ){
    Log::info( "Header comment size must be <= 70" );
    throw;
  }
  return *this;
}
