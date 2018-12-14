template< typename Arg,
          utility::Require< true, IsNormal, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  return std::forward< Arg >( arg );
}

template< typename Arg,
          utility::Require< false, IsNormal, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  auto sum = ranges::accumulate( arg, 0.0 );
  if( sum != 1.0 ){
    Log::error( "range is not normalized" );
    Log::info( "sum over range = {}", sum );

    throw exceptions::NotNormal( "range is not normalized" );
  }

  return std::forward< Arg >( arg );
}
