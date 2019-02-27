template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& energies( Range&& energies ){
  try{
    this->energies_ =  std::move( 
      details::verify::sorted( details::verify::positive( energies ) ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "energy values must be all positive" );
    throw;
  } catch( details::verify::exceptions::Unsorted& e ){
    Log::info( "energy values must be sorted" );
    throw;
  }
}
