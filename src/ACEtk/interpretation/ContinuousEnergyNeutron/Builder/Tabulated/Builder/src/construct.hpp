Tabulated< T > construct(){ 
  try{
    details::verify::equalSize( this->x_.value(), 
                               this->y_.value() );
  } catch( std::range_error& e){
    Log::error( "Tabulated x and y values must have the same size" );
    throw;
  }

  if( !boundaries_ != !schemes_ ){
    Log::error( "Tabulated boundaries and schemes must either be both "
               "specified or neither specified" );
    throw std::exception();
  }
  else if( ( not boundaries_ ) and ( not schemes_ ) ){
    return {
      {},
          std::move( this->x_.value() ),
          std::move( this->y_.value() ) 
    }; 
  }
  try{
    details::verify::equalSize( this->boundaries_.value(), 
                               this->schemes_.value() );
    return {
      std::move( std::make_pair( 
              this->boundaries_.value(), 
              this->schemes_.value() ) ),
          std::move( this->x_.value() ),
          std::move( this->y_.value() ) 
    }; 
  } catch( std::range_error& e){
    Log::error( "Tabulated interpolation boundaries and schemes must "
               "be the same size" );
    throw;
  }
}
