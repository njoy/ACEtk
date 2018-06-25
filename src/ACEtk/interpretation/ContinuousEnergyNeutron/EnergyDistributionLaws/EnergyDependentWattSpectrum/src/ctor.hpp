template< typename Range >
EnergyDependentWattSpectrum( 
    Range& aNBT, Range& aINT, Range& aEnergies, Range& a,
    Range& bNBT, Range& bINT, Range& bEnergies, Range& b )
try:
  aParameters( ENDFInterpolationParameters( aNBT, aINT ),
      Table::Slice{ aEnergies.begin(), aEnergies.end() } ),
  aValues_( Table::Slice{ a.begin(), a.end() } ),
  bParameters( ENDFInterpolationParameters( bNBT, bINT ),
      Table::Slice{ bEnergies.begin(), bEnergies.end() } ),
  bValues_( Table::Slice{ b.begin(), b.end() } )
{
  if( aParameters.incidentEnergies().size() != aValues_.size() ){
    njoy::Log::error( 
      "The number of a values must be the same as \n"
      "the number of incident energies for a's." );
    njoy::Log::info( "# a values: {}, # incident energies for a's: {}",
                     aValues_.size(), aParameters.incidentEnergies().size() );
    throw std::exception();
  }

  if( bParameters.incidentEnergies().size() != bValues_.size() ){
    njoy::Log::error( 
      "The number of b values must be the same as \n"
      "the number of incident energies for b's." );
    njoy::Log::info( "# b values: {}, # incident energies for b's: {}",
                     bValues_.size(), bParameters.incidentEnergies().size() );
    throw std::exception();
  }
} catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing EnergyDependentWattSpectrum" );
  throw e;
}
