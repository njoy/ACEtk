template< typename Range >
AngularDistribution( int INTMU, Range& energies,
                   std::vector< SecondaryDistribution >&& distributions ):
  interpolationParameter_( INTMU ),
  energyGrid_( Table::Slice{ energies.begin(), energies.end() } ),
  cosineDistributions_( std::move( distributions ) )
{
  if( cosineDistributions_.size() != energyGrid_.size() ){
    njoy::Log::error(
      "There must be one cosine distribution for each energy grid point" );
    njoy::Log::info( "energy gird size: {}, # cosine distributions: {}",
                     energyGrid_.size(), cosineDistributions_.size() );
    njoy::Log::info( "Trouble constucting AngularDistribution" );
    throw std::exception();
  }
}
