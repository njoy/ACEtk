ENDFInterpolationParameters( Table::Slice NBT, Table::Slice INT ):
  NBT_( NBT ),
  schemes_( INT )
{
  if( not details::verify::equalSize( NBT_, schemes_ ) ){
    njoy::Log::info( "NBT and INT must be the same size" );
    throw std::exception();
  }

  if( NBT_.size() ){

    // if( not details::verify::isSortedStrictlyPositive( NBT_ ) ){
    //   njoy::Log::info( "NBT must be sorted and strictly positive." );
    //   throw std::exception();
    // }

    if( not details::verify::interpolationParameters( schemes_ ) ){
      njoy::Log::info( "Invalid ENDF interpolation schem found." );
      throw std::exception();
    }
  } // NBT_.size()
}

template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
ENDFInterpolationParameters( Range& NBT, Range& INT )
  try:
    ENDFInterpolationParameters(
      Table::Slice{ NBT.begin(), NBT.end() },
      Table::Slice{ INT.begin(), INT.end() } )
{ } catch( const std::exception& e ){
  njoy::Log::info( 
      "Trouble encountered constructing ENDFInterpolationParameters" );
  throw e;
}
