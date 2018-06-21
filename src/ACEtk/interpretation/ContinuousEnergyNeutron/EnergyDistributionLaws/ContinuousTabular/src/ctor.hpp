ContinuousTabular( ENDFInterpolationParameters&& interp,
                   Table::Slice energies,
                   std::vector< Distribution >&& distributions ):
  interpolationParameters_( interp ),
  incidentEnergies_( energies ),
  distributions_( distributions )
{
  if( interpolationParameters_.NBT().back() != incidentEnergies_.size() ){
    njoy::Log::error( 
      "The last value of NBT must be the size of the incident energies." );
    njoy::Log::info( "NBT.back(): {}, # incident energies: {}",
      interpolationParameters_.NBT().back(), incidentEnergies_.size() );
    throw std::exception();
  }

  if( interpolationParameters_.NBT().size() >= incidentEnergies_.size() ){
    njoy::Log::error( 
      "The number of inerpolation regions must be smaller than\n"
      "the number of incident energies." );
    njoy::Log::info( "# interpolations regions: {}", 
                     interpolationParameters_.NBT().size() );
    njoy::Log::info( "# incident energies: {}", 
                     incidentEnergies_.size() );
    throw std::exception();
  }

  if( distributions_.size() != incidentEnergies_.size() ){
    njoy::Log::error(
      "There must be one secondary distribution for each incident energy" );
    njoy::Log::info( "# incident energies: {}, # secondary distributions: {}",
                     incidentEnergies_.size(), distributions_.size() );
    throw std::exception();
  }
}

template< typename Range >
ContinuousTabular( Range& NBT, Range& INT, 
                   Range& energies, 
                   std::vector< Distribution >&& distributions )
  try:
    ContinuousTabular( 
      ENDFInterpolationParameters( NBT, INT ),
      Table::Slice{ energies.begin(), energies.end() },
      std::forward< std::vector< Distribution > >( distributions )
    )
{ } catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing ContinuousTabular" );
}
