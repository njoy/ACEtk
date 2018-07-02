Tabulated( ENDFInterpolationParameters&& interp,
           Slice energies, 
           Slice nubar) :
  interpolationParameters_( interp ),
  energies_( energies ),
  nubar_( nubar )
{
  if( energies_.size() != nubar.size() ){
    njoy::Log::error( "incident energies and nubar must be the same size" );
    njoy::Log::info( "energies size: {}, nubar size: {}", 
                     energies_.size(), nubar_.size() );
    throw std::exception();
  }

  if( not details::verify::sorted( energies_ ) ){
    njoy::Log::info( "incident energies must be sorted" );
    throw std::exception();
  }

#if ACETK_CHECK
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
             Table::slice( energies ),
             Table::slice( nubar ) )
{ } catch( const std::exception& e ){
  njoy::Log::info( 
      "Trouble encountered constructing Tabulated nubar" );
  throw e;
}
