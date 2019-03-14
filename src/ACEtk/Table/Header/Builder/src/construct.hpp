Header construct(){
  try{
    return Header{
      processDate_.value(),
      processTemperature_.value(),
      atomicWeightRatio_.value(),
      std::move( szaid_.value() ),
      std::move( comments_ )
    };
  } catch( std::bad_optional_access& e ){
    Log::error( "Some component of Header not built" );
    throw;
  }
}
