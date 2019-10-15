Data construct() {
  try{
    details::verify::equalSize( 
      this->P_.value(), 
      this->T_.value(),   
      this->C_.value()
    );
    return { std::move( P_.value() ), 
             std::move( T_.value() ), 
             std::move( C_.value() ) };
  } catch( std::range_error& e ){
    Log::info( "P, T, and C must all be the same size." );
    Log::info( "P.size = {}", P_.value().size() );
    Log::info( "T.size = {}", T_.value().size() );
    Log::info( "C.size = {}", C_.value().size() );
    throw;
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble creating Tabular Linear Functions data." );
    Log::info( "Some component has not been defined." );
    throw;
  }
}
