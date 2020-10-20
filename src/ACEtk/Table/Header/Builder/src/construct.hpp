Header construct(){
  try{
    Header head{
      processDate_.value(),
      processTemperature_.value(),
      atomicWeightRatio_.value(),
      std::move( szaid_.value() ),
      std::move( comments_ )
    };

    head.mat = mat_;
    head.source = source_;

    return head;

  } catch( std::bad_optional_access& e ){
    Log::error( "Some component of Header not built" );
    throw;
  }
}
