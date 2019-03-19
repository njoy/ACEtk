template< typename T >
void equalSize( T& t, std::string name ){
  try{
    details::verify::equalSize( t.value(), this->cosineGrid_.value() );
  } catch( std::range_error& e){
    Log::info( "{} must be the same size as cosine bins", name );
    throw;
  } catch( std::bad_optional_access& e ){
    Log::error( "{} has not been initialized", name );
    throw;
  }

}
