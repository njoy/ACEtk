Tabulated< T > construct(){ 
  try{
    details::verify::equalSize( this->x_.value(), 
                               this->y_.value() );
  } catch( std::range_error& e){
    Log::info( "Tabulated x and y values must have the same size" );
    throw;
  } catch( std::bad_optional_access& ){
    Log::info( 
      "Either the x or y component of a Tabulated distribution isn't specified" 
    );
  }

  std::optional< opt_t > parameters = std::nullopt;

  if( !boundaries_ != !schemes_ ){
    Log::error( "Tabulated boundaries and schemes must either be both "
               "specified or neither specified" );
    throw std::exception();
  }
  else if( ( boundaries_ ) and ( schemes_ ) ){
    try{
      details::verify::equalSize( this->boundaries_.value(), 
                                 this->schemes_.value() );
      parameters = std::make_optional< opt_t >( 
        std::make_pair( 
          this->boundaries_.value(), 
          this->schemes_.value()
        )
      );

    } catch( std::range_error& e){
      Log::error( "Tabulated interpolation boundaries and schemes must "
                 "be the same size" );
      throw;
    }
  }
  return {
    std::move( parameters ),
    std::move( this->x_.value() ),
    std::move( this->y_.value() ) 
  }; 
}
