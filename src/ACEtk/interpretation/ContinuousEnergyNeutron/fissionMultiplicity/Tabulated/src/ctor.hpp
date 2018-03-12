Tabulated( std::optional< Slice > interpolationParameters, 
           std::optional< Slice > interpolationSchemes, 
           Slice energies, 
           Slice nubar) :
  NBT( interpolationParameters ),
  INT( interpolationSchemes ),
  energies_( energies ),
  nubar_( nubar )
{
  assert( bool( NBT ) == bool( INT ) );
  assert( not bool( NBT ) or ( NBT->size() == INT->size() ) );
  assert( energies_.size() == nubar.size() );

#if ACETK_CHECK
  // sorted energies
  // sorted NBT
  // positive nubar
  // INT must be in [1,8)
#endif
}
