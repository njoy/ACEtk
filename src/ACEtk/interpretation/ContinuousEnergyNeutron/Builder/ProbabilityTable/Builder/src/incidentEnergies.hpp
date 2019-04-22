template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& incidentEnergies( Range&& energies ){
  try{
    this->incidentEnergies_ = std::make_optional<
      dvP< dvS< 
        std::vector< double > > > >(
          std::move( energies ) | ranges::to_vector );
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "Probability table incident energies must be all postive" );
    throw;
  } catch( details::verify::exceptions::Unsorted& e ){
    Log::info( "Probability table incident energies must be sorted" );
    throw;
  }
}
