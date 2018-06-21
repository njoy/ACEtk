ContinuousTabular( ENDFInterpolationParameters&& interp,
                   Table::Slice energies ):
  interpolationParameters_( interp ),
  incidentEnergies_( energies )
{
}

template< typename Range >
ContinuousTabular( Range& NBT, Range& INT, Range& energies )
  try:
    ContinuousTabular( 
      ENDFInterpolationParameters( NBT, INT ),
      Table::Slice{ energies.begin(), energies.end() }
    )
{ } catch( const std::exception& e ){
  njoy::Log::info(
    "Trouble encountered constructing ContinuousTabular" );
}
