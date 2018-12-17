template< typename Arg,
          utility::Require< true, IsCosineBins, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  return std::forward< Arg >( arg );
}

template< typename Arg,
          utility::Require< false, IsCosineBins, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  try{
    details::verify::cosines( arg );
    return sorted( std::forward< Arg >( arg ) );
  } catch( details::verify::exceptions::Unsorted& s ){
    Log::info( "Cosine bins must be sorted" );
    throw;
  } catch( details::verify::exceptions::InvalidCosine& s ){
    Log::info( "Cosine bin values must be in the range: [ -1, 1 ]." );
    throw;
  }
}

