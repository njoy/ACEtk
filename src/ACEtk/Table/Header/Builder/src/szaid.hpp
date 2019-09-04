Builder& szaid( const std::string& z ){
  try{ 
    this->szaid_ = std::make_optional< SZAID >( z );
  } catch( std::exception& ){
    Log::info( "(S)ZAID size must be <= 24" );
    throw;
  }
  return *this;
}

Builder& zaid( const std::string& z ){
  return szaid( z );
}
