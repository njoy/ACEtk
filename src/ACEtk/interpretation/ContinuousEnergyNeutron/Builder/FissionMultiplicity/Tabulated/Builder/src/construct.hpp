Tabulated1D construct(){ 
  try{
    details::verify::equalSize( this->energies_.value(), 
                                this->multiplicities_.value() );
  } catch( std::range_error& e){
    Log::info( "energies and multiplicities must be the same size" );
    throw;
  }

  return Tabulated{
    std::move( this->energies_.value() ),
    std::move( this->multiplicities_.value() ) 
  }; 
}
