SecondaryDistribution( int INTT, 
              Table::Slice energies,
              CoupledDensityFunctions&& DFs ):
  interpolationParameter_( INTT ),
  energyGrid_( energies ),
  densityFunctions_( DFs )
{
  try{
    details::verify::equalSize( energyGrid_, densityFunctions_.PDF() );
  } catch( std::range_error& e ){
    njoy::Log::info( 
      "outgoing energy grid and density functions ar no the same size" );
    throw;
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
