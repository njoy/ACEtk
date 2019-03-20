Builder& materialNumber( std::string m ){
  try{ 
    this->mat_ = m;
  } catch( std::exception& ){
    Log::info( "Material number must be size <= 10" );
    Log::info( "Received material number of size: {}", m.size() );
    throw;
  }
  return *this;
}

Builder& materialNumber( int m ){
  return materialNumber( std::to_string( m ) );
}
