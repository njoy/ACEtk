template< typename Arg,
          utility::Require< true, IsStrictlyPositive, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  return std::forward< Arg >( arg );
}

template< typename Arg,
          utility::Require< false, IsStrictlyPositive, Arg > = true,
          utility::Require< true, IsSorted, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  if( *( arg.begin() ) <= 0.0 ){
    njoy::Log::error( "range is not all strictly positive" );
    njoy::Log::info( "Non-strictly positive element ({}) found at index: {}",
                     *( arg.begin() ), 0 );
    throw NotStrictlyPositiveException
    { "(sorted) range is not all strictly positive" };
  }
  return std::forward< Arg >( arg );
}

template< typename Arg,
          utility::Require< false, IsStrictlyPositive, Arg > = true,
          utility::Require< false, IsSorted, Arg > = true,
          utility::Require< true, utility::is_range, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  const auto firstNegative =
    ranges::find_if( arg, []( auto&& e ){ return e <= 0; } );

  if( firstNegative != arg.end() ){
    njoy::Log::error( "range is not all strictly positive" );
    njoy::Log::info(
      "First non-strictly positve element ({}) found at index: {}",
      *firstNegative, std::distance(  arg.begin(), firstNegative ) );
    throw NotStrictlyPositiveException
    { "range is not all strictly positive" };
  }
  return std::forward< Arg >( arg );
}

