AngularDistribution construct(){
  
  try{
    details::verify::equalSize( this->representations_, 
                                this->energyGrid_.value() );
  } catch( std::range_error& e){
    Log::info( 
      "There must be an angular distribution for every energy grid value." );
    throw;
  }

  return AngularDistribution{
    std::move( energyGrid_.value() ),
    std::move( representations_ )
  };
}

