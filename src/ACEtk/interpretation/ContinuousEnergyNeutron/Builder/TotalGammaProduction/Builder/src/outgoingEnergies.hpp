template< typename RoR >
Builder& outgoingEnergies( RoR&& energies){

  auto toPositive = []( auto&& r ){
    return details::verify::positive( std::forward< decltype( r ) >( r ) );
  };
  try{
    this->outgoingEnergies_ = energies
      | ranges::view::transform(
          hana::compose( toPositive, details::make_array< 20 > ) 
        )
      | ranges::make_pipeable( details::make_array< 30 > );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "outgoing energies must be all positive" );
    throw;
  }
}

