Builder& primaryFlag( int flag ){
  if( ( flag < 0 ) or ( flag > 2 ) ){
    Log::error( "Invalid primary flag value: {}", flag );
    Log::info( "valid primary flag values are: 0, 1, or 2" );
    throw std::exception();
  }

  primaryFlag_ = flag;
  return *this;
}
