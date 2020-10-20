template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& incidentEnergies( Range&& energies ){
  try{
    this->incidentEnergies_ = std::move( 
      details::verify::positive( details::verify::sorted( energies ) ) );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "Probability table incident energies must be all postive" );
    throw;
  } catch( details::verify::exceptions::Unsorted& e ){
    Log::info( "Probability table incident energies must be sorted" );
    throw;
  }
}
