template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& effectiveTemperature( Range&& energies ){
  try{
    this->y( std::move( details::verify::positive( energies ) ));
    return *this;
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "Effective temperature values must be all positive" );
    throw;
  }
}
