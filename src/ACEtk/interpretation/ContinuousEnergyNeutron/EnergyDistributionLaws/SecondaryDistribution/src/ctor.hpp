SecondaryDistribution( int INTT, 
              Table::Slice energies,
              CoupledDensityFunctions&& DFs ):
  interpolationParameter_( INTT ),
  energyGrid_( energies ),
  densityFunctions_( DFs )
{
  if( energyGrid_.size() != densityFunctions_.size() ){
    njoy::Log::error( 
      "outgoing energy grid and density functions must have same size" );
    njoy::Log::info( "energy grid size: {}", energyGrid_.size() );
    njoy::Log::info( "density function size: {}", densityFunctions_.size() );
    throw std::exception();
  }
}

template< typename Range >
SecondaryDistribution( int INTT, Range& energies, Range& PDF, Range& CDF )
  try:
    SecondaryDistribution( 
      INTT,
      Table::Slice{ energies.begin(), energies.end() },
      CoupledDensityFunctions{ PDF, CDF }
    )

{ } catch( std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing Law4::Distribution" );
}
