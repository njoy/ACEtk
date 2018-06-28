template< typename Range >
LaboratoryAngleEnergyLaw( Range& NBT, Range& INT, Range& energies,
                          std::vector< AngularDistribution >&& distributions )
try:
  InterpolatedEnergies( NBT, INT, energies ),
  angularDistributions_( std::move( distributions ) )
{
  if( incidentEnergies().size() != angularDistributions_.size() ){
    njoy::Log::error( 
      "There must be one angular distribution for each energy grid point" );
    njoy::Log::info( "energy grid size: {}, # angular distributions: {}",
                     incidentEnergies().size(), angularDistributions_.size() );
    throw std::exception();
  }
} catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing LaboratoryAngleEnergyLaw" );
  throw e;
}
