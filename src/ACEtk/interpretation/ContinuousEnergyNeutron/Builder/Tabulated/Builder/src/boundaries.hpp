template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Derived& boundaries( Range&& boundaries ){
  try{
    this->boundaries_ = std::move( 
        details::verify::strictlyPositive( 
          details::verify::sorted( boundaries ) ) );
    return static_cast< Derived& >( *this );
  } catch( details::verify::exceptions::NotPositive& ){
    Log::info( "Tabulated interpolation boundaries must be all positive." );
    throw;
  } catch( details::verify::exceptions::Unsorted& ){
    Log::info( "Tabulated interpolation boundaries must sorted." );
    throw;
  }
}
