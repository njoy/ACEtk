Builder& addReaction( Reaction&& reaction ){
  if( reactions_.insert( 
          std::make_pair( reaction.MT, std::move( reaction ) ) ).second ){
    return *this;
  }
  else{
    njoy::Log::error( 
        "Duplicate reaction number (MT): {} added.", reaction.MT );
    throw std::exception();
  }
}
