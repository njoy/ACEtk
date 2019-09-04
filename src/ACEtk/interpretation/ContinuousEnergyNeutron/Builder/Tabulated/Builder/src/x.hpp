template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Derived& x( Range&& x ){
  try{
    this->x_ = std::move( details::verify::sorted( x ) );
    return static_cast< Derived& >( *this );
  } catch( details::verify::exceptions::Unsorted& ){
    Log::info( "Tabulated independent variables (x) must be sorted" );
    throw;
  }
}
