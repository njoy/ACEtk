Builder& outgoingEnergies( 
    std::array< std::array< double, 20 >, 30 >&& energies){
  try{
    // this->outgoingEnergies_ = std::move( 
    //   details::verify::isPositive( energies ) );
    this->outgoingEnergies_ = std::move( energies );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "outgoing energies must be all positive" );
    throw;
  }
}

