template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder&
yields( Range&& yields ){
  try{
    return this->y( details::verify::positive( yields | ranges::to_vector ) );
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "yield values must be all positive" );
    throw;
  }
}
