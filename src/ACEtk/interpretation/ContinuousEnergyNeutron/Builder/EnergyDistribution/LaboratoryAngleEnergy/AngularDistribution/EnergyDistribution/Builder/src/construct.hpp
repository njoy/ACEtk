EnergyDistribution construct(){
  try{
    details::verify::equalSize( this->energies_.value(), this->pdf_.value() );
    details::verify::equalSize( this->pdf_.value(), this->cdf_.value() );
  } catch( std::range_error& e ){
    Log::info( "energies, pdf, and cdf, must all be the same size." );
    throw;
  }

  try{
    return {
      std::move( interpolationParameter_.value() ),
      std::move( energies_.value() ),
      std::move( pdf_.value() ),
      std::move( cdf_.value() )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( 
      "Trouble when creating laboratory angular energy distribution data." );
    Log::info( "Some component has not been defined." );
    throw;
  }
}