AngularDistribution::Builder 
angularDistribution(){ 
  if( this->isNeutronProducing() ){
    return AngularDistribution::Builder{ *this }; 
  } else {
    Log::error( "Reaction: {} does not produce secondary neutrons." );
    Log::info( "Must not specify angular distribution." );
    throw std::range_error( "Angular distribution not allowed." );
  }
}
