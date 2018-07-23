Tabulated( ENDFInterpolationParameters&& interp,
           Slice energies, 
           Slice nubar) :
  interpolationParameters_( interp ),
  energies_( energies ),
  nubar_( nubar )
{
  try{
    details::verify::equalSize(energies, nubar);
  } catch( std::range_error& e ){
    njoy::Log::info( "incident energies and nubar must be the same size" );
    throw e;
  }

  try{
    details::verify::positive( details::verify::sorted( energies_ ) );
  } catch( details::verify::exceptions::NotPositive& e ){
    njoy::Log::info( "incident energies must be positive" );
    throw e;
  } catch( details::verify::exceptions::Unsorted& e ){
    njoy::Log::info( "incident energies must be sorted" );
    throw e;
  }

  try{
    details::verify::positive( nubar );
  } catch( details::verify::exceptions::NotPositive& e ){
    njoy::Log::info( "nubar values must be positive" );
    throw e;
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
