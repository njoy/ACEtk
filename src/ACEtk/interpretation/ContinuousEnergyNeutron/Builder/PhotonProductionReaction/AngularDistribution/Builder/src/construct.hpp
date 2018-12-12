AngularDistribution construct(){
  try{
    details::verify::equalSize( this->cosineBins_.value(), 
                                this->energyGrid_.value() );
  } catch( std::range_error& e){
    Log::info( "energy grid size must equal the size of the cosine bins" );
    throw;
  }
  return AngularDistribution{
    std::move( energyGrid_.value() ),
    std::move( cosineBins_.value() )
  };
}

