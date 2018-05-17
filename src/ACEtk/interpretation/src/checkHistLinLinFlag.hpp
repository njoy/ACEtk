void checkHistLinLinFlag( int flag ) { 
  if( (flag != 0) and (flag != 1) ){
    Log::error( "interpolation flag must be 0 or 1, set as: {}", flag );
    throw std::exception();
  }
}

