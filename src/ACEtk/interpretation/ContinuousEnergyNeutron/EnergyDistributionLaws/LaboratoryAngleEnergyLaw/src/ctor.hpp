template< typename Range >
LaboratoryAngleEnergyLaw( Range& NBT, Range& INT, Range& energies,
                          std::vector< AngularDistribution >&& distributions )
try:
  BaseLaw( NBT, INT, energies ),
  angularDistributions_( std::move( distributions ) )
{
} catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing ContinuousTabular" );
  throw e;
}
