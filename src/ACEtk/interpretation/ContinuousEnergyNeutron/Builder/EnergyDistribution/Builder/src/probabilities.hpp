template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& probabilities( Range&& probabilities ){
  try{
    this->y( std::move( details::verify::positive( probabilities ) ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "energy values must be all positive" );
    throw;
  } catch( details::verify::exceptions::Unsorted& e ){
    Log::info( "energy values must be sorted" );
    throw;
  }
}
