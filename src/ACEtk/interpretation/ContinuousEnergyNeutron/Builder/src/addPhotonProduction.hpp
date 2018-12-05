Builder& addPhotonProduction( int MT, PhotonReaction&& reaction ){
  if( photonReactions_.insert( 
          std::make_pair( MT, std::move( reaction ) ) ).second ){
    return *this;
  }
  else{
    njoy::Log::error( 
        "Duplicate photon productionreaction number (MT): {} added.", MT );
    throw std::exception();
  }
}
