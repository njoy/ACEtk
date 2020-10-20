template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& energies( Range&& energies ){
  try{
    this->energies_ =  std::move( 
      details::verify::positive( details::verify::sorted( energies ) ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "Trouble adding energies to LAW=4 data." );
    Log::info( "energy values must be all positive" );
    throw;
  } catch( details::verify::exceptions::Unsorted& e ){
    Log::info( "Trouble adding energies to LAW=4 data." );
    Log::info( "energy values must be sorted" );
    throw;
  }
}
