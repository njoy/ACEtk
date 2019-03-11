template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Derived& energies( Range&& energies ){
  try{
    this->x_ =  std::move( 
      details::verify::sorted( details::verify::positive( 
              energies | ranges::to_vector ) ) );
    return static_cast< Derived& >( *this );
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "energy values must be all positive" );
    throw;
  } catch( details::verify::exceptions::Unsorted& e ){
    Log::info( "energy values must be sorted" );
    throw;
  }
}
