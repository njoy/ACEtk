Tabulated( ENDFInterpolationParameters&& interp,
           Slice energies, 
           Slice nubar) :
  interpolationParameters_( interp ),
  energies_( energies ),
  nubar_( nubar )
{
  if( not details::verify::equalSize(energies, nubar) ){
    njoy::Log::error( "incident energies and nubar must be the same size" );
    throw std::exception();
  }

  // if( not details::verify::isSortedPositive( energies_ ) ){
  //   njoy::Log::info( "incident energies must be sorted" );
  //   throw std::exception();
  // }

  if( not details::verify::isPositive( nubar ) ){
    njoy::Log::info( "nubar values must be positive" );
    throw std::exception();
  }
}

template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
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
