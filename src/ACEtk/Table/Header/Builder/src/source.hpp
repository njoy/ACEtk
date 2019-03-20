Builder& source( std::string s ){
  try{ 
    this->source_ = s;
  } catch( std::exception& ){
    Log::info( "source must be size <= 24" );
    Log::info( "Received source of size: {}", s.size() );
    throw;
  }
  return *this;
}
