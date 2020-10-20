AngularDistribution construct() {
  try{
    details::verify::equalSize( this->cosines_.value(), 
                                this->energyDistributions_ );
  } catch( std::range_error& e ){
    Log::info( "cosines and energy distributions must be the same size." );
    throw;
  }

  try{
    return {
      interpolationParameter_.value(),
      std::move( cosines_.value() ),
      std::move( energyDistributions_ )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating laboratory angle energy "
                "angular distribution data." );
    Log::info( "Some component has not been defined." );
    throw;
  }
}
