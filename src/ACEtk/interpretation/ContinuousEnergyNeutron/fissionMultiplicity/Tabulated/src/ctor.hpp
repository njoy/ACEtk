Tabulated( ENDFInterpolationParameters&& interp,
           Slice energies, 
           Slice nubar) :
  interpolationParameters_( interp ),
  energies_( energies ),
  nubar_( nubar )
{
  assert( energies_.size() == nubar.size() );

#if ACETK_CHECK
  // sorted energies
  // sorted NBT
  // positive nubar
  // INT must be in [1,8)
#endif
}

template< typename Range >
Tabulated( Range& NBT, Range& INT,
           Range& energies, Range& nubar )
try:
  Tabulated( ENDFInterpolationParameters( NBT, INT ), 
             Table::Slice{ energies.begin(), energies.end() }, 
             Table::Slice{ nubar.begin(), nubar.end() } )
{ } catch( const std::exception& e ){
  njoy::Log::info( 
      "Trouble encountered constructing Tabulated nubar" );
  throw e;
}
