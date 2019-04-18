template< typename M, typename R >
Builder& addReaction( M& rMap, R&& reaction ){
  if( rMap.insert( 
          std::make_pair( reaction.MT, std::move( reaction ) ) ).second ){
    return *this;
  }
  else{
    njoy::Log::error( 
        "Duplicate reaction number (MT): {} added.", reaction.MT );
    throw std::exception();
  }
}

Builder& addReaction( Reaction::NeutronProducing&& reaction ){
  return this->addReaction( this->neutronProducingReactions_, reaction );
}

Builder& addReaction( Reaction::NonNeutronProducing&& reaction ){
  return this->addReaction( this->nonNeutronProducingReactions_, reaction );
}
