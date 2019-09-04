Builder& materialNumber( const std::string& m ){
  try{ 
    this->mat_ = std::make_optional< MAT >( m );
  } catch( std::exception& ){
    Log::info( "Material number must be size <= 10" );
    throw;
  }
  return *this;
}

Builder& materialNumber( int m ){
  return materialNumber( std::to_string( m ) );
}
