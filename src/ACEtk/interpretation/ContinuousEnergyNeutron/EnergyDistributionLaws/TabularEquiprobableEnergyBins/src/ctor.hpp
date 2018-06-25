template< typename Range >
TabularEquiprobableEnergyBins( Range& NBT, Range& INT, Range& energies, 
                               size_t NET, Range& outgoingEnergies)
try:
  BaseLaw( NBT, INT, energies ),
  outgoingEnergyTables_( 
    make( Table::Slice{ outgoingEnergies.begin(), outgoingEnergies.end() },
          incidentEnergies_.size(), NET ) )
{ } catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing TabularEquiprobableEnergyBins" );
}
