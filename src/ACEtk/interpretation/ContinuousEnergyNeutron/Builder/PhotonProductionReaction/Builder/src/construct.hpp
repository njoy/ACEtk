PhotonProductionReaction construct(){
  if( yields_ and crossSection_ ){
    Log::error( 
      "Either photon production yields or cross sections can be given; "
      "not both." );
    throw std::exception();
  }
  return PhotonProductionReaction{
    MT,
    yields_,
    crossSection_,
    angularDistribution_.value()
  };
}

