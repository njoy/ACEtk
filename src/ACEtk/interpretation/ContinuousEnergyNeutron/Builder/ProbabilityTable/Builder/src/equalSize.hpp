template< typename T >
void equalSize( T& t, std::string name ){
  try{
    details::verify::equalSize( t.value(), 
                                this->incidentEnergies_.value() );
  } catch( std::range_error& e){
    Log::info( "{} must be the same size as incident energies", name );
    throw;
  } catch( std::bad_optional_access& e ){
    Log::error( "{} has not be initialized", name );
    throw;
  }

}
