template< typename Range >
ContinuousTabular( Range& NBT, Range& INT, 
                   Range& energies, 
                   std::vector< Distribution >&& distributions )
try:
  BaseLaw( NBT, INT, energies ),
  distributions_( distributions )
{
  if( distributions_.size() != incidentEnergies().size() ){
    njoy::Log::error(
      "There must be one secondary distribution for each incident energy" );
    njoy::Log::info( "# incident energies: {}, # secondary distributions: {}",
                     incidentEnergies().size(), distributions_.size() );
    throw std::exception();
  }
} catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing ContinuousTabular" );
}
