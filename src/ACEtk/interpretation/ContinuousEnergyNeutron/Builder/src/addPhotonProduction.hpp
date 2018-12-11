Builder& addPhotonProduction( PhotonProductionReaction&& reaction ){
  if( photonProductionReactions_.insert( 
          std::make_pair( reaction.MT, std::move( reaction ) ) ).second ){
    return *this;
  }
  else{
    njoy::Log::error( 
        "Duplicate photon production reaction number (MT): {} added.", 
        reaction.MT );
    throw std::exception();
  }
}
