Data construct(){
  try{
    details::verify::equalSize( this->energies_.value(), this->pdf_.value() );
    details::verify::equalSize( this->pdf_.value(), this->cdf_.value() );
    details::verify::equalSize( this->cdf_.value(), 
                                this->precompoundFraction_.value() );
    details::verify::equalSize( this->cdf_.value(), 
                                this->angularDistributionSlope_.value() );
  } catch( std::range_error& e ){
    Log::info( 
      "Energies, pdf, cdf, precompound fraction, and angulardistribution slope"
      " must all be the same size." );
    throw;
  }

  try{
    return {
      std::move( interpolationParameter_.value() ),
      std::move( energies_.value() ),
      std::move( pdf_.value() ),
      std::move( cdf_.value() ),
      std::move( precompoundFraction_.value() ),
      std::move( angularDistributionSlope_.value() )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating continuous tabular distribution data." );
    Log::info( "Some component has not been defined." );
    throw;
  }
}