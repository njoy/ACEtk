TabularEquiprobableEnergyBins( ENDFInterpolationParameters&& interp,
                               Table::Slice energies,
                               size_t NET, Table::Slice outgoingEnergies):
  interpolationParameters_( interp ),
  incidentEnergies_( energies ),
  outgoingEnergyTables_( make( outgoingEnergies, incidentEnergies_.size(),
                              NET ) )
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
TabularEquiprobableEnergyBins( Range& NBT, Range& INT, Range& energies, 
                               size_t NET, Range& outgoingEnergies)
  try:
    TabularEquiprobableEnergyBins( 
      ENDFInterpolationParameters( NBT, INT ),
      Table::Slice{ energies.begin(), energies.end() },
      NET, Table::Slice{ outgoingEnergies.begin(), outgoingEnergies.end() }
    )
{ } catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing TabularEquiprobableEnergyBins" );
}
