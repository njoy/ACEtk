ENDFInterpolationParameters( Table::Slice NBT, Table::Slice INT ):
  NBT_( NBT ),
  schemes_( INT )
{
  try{
    details::verify::equalSize( NBT_, schemes_ );
  } catch( std::range_error& e ){
    njoy::Log::info( "NBT and INT must be the same size" );
    throw e;
  }

  if( NBT_.size() ){

    // if( not details::verify::isSortedStrictlyPositive( NBT_ ) ){
    //   njoy::Log::info( "NBT must be sorted and strictly positive." );
    //   throw std::exception();
    // }

    try{ 
      details::verify::interpolationParameters( schemes_ );
    } catch( details::verify::exceptions::InvalidENDFInterpolationParameter& e ){
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
