template< typename Arg,
          utility::Require< true, IsCDF, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  return std::forward< Arg >( arg );
}

template< typename Arg,
          utility::Require< false, IsCDF, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  try{
    return positive( sorted( std::forward< Arg >( arg ) ) );
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "CDFs must be all positive" );
    throw exceptions::InvalidCDF( "CDFs must be all positive" );
  } catch( details::verify::exceptions::Unsorted& s ){
    Log::info( "CDFs must be sorted" );
    throw exceptions::InvalidCDF( "CDFs must be sorted" );
  }
}
