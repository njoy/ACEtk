template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cosineBins( int index, Range&& bins ){

  try{
    this->cosineBins_[ index ] = details::verify::cosineBins( 
      std::move( bins ) );
    return *this;
  } catch( details::verify::exceptions::InvalidCosine& e ){
    Log::info( "Trouble adding cosine bins (at index: {}) "
               "for photon production angular distribution", index );
    throw;
  }
}
