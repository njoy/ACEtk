TabularEquiprobableEnergyBins( ENDFInterpolationParameters&& interp,
                               Table::Slice energies,
                               int NET, Table::Slice outgoingEnergies):
  interpolationParameters_( interp ),
  incidentEnergies_( energies ),
  outgoingEnergyTables_( make( outgoingEnergies, incidentEnergies_.size(),
                              NET ) )
    // outgoingEnergies | ranges::view::chunk( incidentEnergies_.size() ) )
{ }

template< typename Range >
TabularEquiprobableEnergyBins( Range& NBT, Range& INT, Range& energies, 
                               int NET, Range& outgoingEnergies)
  try:
    TabularEquiprobableEnergyBins( ENDFInterpolationParameters( NBT, INT ),
        Table::Slice{ energies.begin(), energies.end() },
        NET, Table::Slice{ outgoingEnergies.begin(), outgoingEnergies.end() }
        )
{ } catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing TabularEquiprobableEnergyBins" );
}
