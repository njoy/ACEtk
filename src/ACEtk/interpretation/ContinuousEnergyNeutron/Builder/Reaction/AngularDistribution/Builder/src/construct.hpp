AngularDistribution construct(){
  
  try{
    details::verify::equalSize( this->representations_, 
                                this->energyGrid_.value() );
  } catch( std::range_error& e){
    Log::info( 
      "There must be an angular distribution for every energy grid value." );
    throw;
  }

  try{
    return AngularDistribution{
      std::move( energyGrid_.value() ),
      std::move( representations_ )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a Reaction::AngularDistribution object" );
    Log::info( "Some component has not been defined" );
    throw;
  }
}

