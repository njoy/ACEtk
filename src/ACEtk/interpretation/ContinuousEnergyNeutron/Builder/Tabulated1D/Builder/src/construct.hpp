Tabulated1D construct(){ 
  try{
    details::verify::equalSize( this->boundaries_.value(), 
                                this->schemes_.value() );
  } catch( std::range_error& e){
    Log::info( "Interpolation boundaries and schemes must be the same size" );
    throw;
  }
  try{
    details::verify::equalSize( this->x_.value(), 
                                this->y_.value() );
  } catch( std::range_error& e){
    Log::info( "x and y must be the same size" );
    throw;
  }

  return Tabulated1D{
    std::move( this->boundaries_.value() ),
    std::move( this->schemes_.value() ),
    std::move( this->x_.value() ),
    std::move( this->y_.value() ) 
  }; 
}