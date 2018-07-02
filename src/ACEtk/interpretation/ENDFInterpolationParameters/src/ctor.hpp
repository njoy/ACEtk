ENDFInterpolationParameters( Table::Slice NBT, Table::Slice INT ):
  NBT_( NBT ),
  schemes_( INT )
{
  if( not details::verify::equalSize( NBT_, schemes_ ) ){
    njoy::Log::info( "NBT and INT must be the same size" );
    throw std::exception();
  }

  if( NBT_.size() ){

    if( not details::verify::sorted_strictlyPositive( NBT_ ) ){
      njoy::Log::info( "NBT must be sorted and strictly positive." );
      throw std::exception();
    }

    int sch{ 0 };
    for( size_t i=0; i<schemes_.size(); i++ ){
      sch = schemes_[i];
      if( not ( ( ( sch >  0 ) and ( sch <  7 ) ) or
                ( ( sch > 10 ) and ( sch < 16 ) ) or
                ( ( sch > 20 ) and ( sch < 26 ) ) )
        ){
        
        njoy::Log::error(
          "Invalid ENDF interpolation scheme ({}) found at index {}", sch, i );
        throw std::exception();
      }
    }
  } // NBT_.size()
}

template< typename Range >
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
