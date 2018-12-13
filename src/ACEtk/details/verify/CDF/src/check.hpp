template< typename Arg,
          utility::Require< true, IsCDF, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  return std::forward< Arg >( arg );
}

template< typename Arg,
          utility::Require< false, IsCDF, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  try{
    return std::forward< Arg >( positive( sorted( arg ) ) );
  } catch( details::verify::exceptions::NotPositive& p ){
    Log::info( "CDFs must be all positive" );
    throw;
  } catch( details::verify::exceptions::Unsorted& s ){
    Log::info( "CDFs must be sorted" );
    throw;
  }
}
