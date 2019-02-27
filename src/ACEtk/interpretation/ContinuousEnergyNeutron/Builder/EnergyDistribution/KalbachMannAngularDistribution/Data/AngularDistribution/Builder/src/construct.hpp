AngularDistribution construct(){
  try{
    details::verify::equalSize( this->cosineGrid_.value(), this->pdf_.value() );
    details::verify::equalSize( this->pdf_.value(), this->cdf_.value() );
  } catch( std::range_error& e ){
    Log::info( 
      "cosine grid, pdf, and cdf, must all be the same size." );
    throw;
  }

  try{
    return {
      std::move( interpolationParameter_.value() ),
      std::move( cosineGrid_.value() ),
      std::move( pdf_.value() ),
      std::move( cdf_.value() )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating continuous tabular distribution data." );
    Log::info( "Some component has not been defined." );
    throw;
  }
}
