InterpolatedEnergies( ENDFInterpolationParameters&& interp,
                   Table::Slice energies ):
  interpolationParameters_( interp ),
  incidentEnergies_( energies )
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
}

template< typename Range >
InterpolatedEnergies( Range& NBT, Range& INT, Range& energies )
  try:
    InterpolatedEnergies( 
      ENDFInterpolationParameters( NBT, INT ),
      Table::Slice{ energies.begin(), energies.end() }
    )
{ } catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing InterpolatedEnergies" );
}

