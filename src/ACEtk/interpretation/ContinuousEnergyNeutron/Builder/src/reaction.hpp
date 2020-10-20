Reaction::Builder reaction( int MT ){ 
  if( MT <= 1 ){
    Log::error( "Reaction numbers must be >1" );
    Log::info( "Given reaction number: {}", MT );
    throw std::range_error( "Invalid reaction number." );
  }
  return Reaction::Builder{ *this, MT }; 
}
