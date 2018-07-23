template< typename Arg,
          utility::Require< false, IsSorted, Arg > = true,
          utility::Require< true, utility::is_range, Range > = true >
decltype( auto ) check( Arg&& arg ){
  auto firstNegative = ranges::find_if( arg, [](auto& e ){ return e <= 0; } );

  if( firstNegative != arg.end() ){
    njoy::Log::error( "range is not all positive" );
    njoy::Log::info(
      "First non-strictly positve element ({}) found at index: {}",
      *firstNegative, std::distance(  arg.begin(), firstNegative ) );
    throw exceptions::NotStrictlyPositive(
      "range is not all strictly positive" );
  }
  return std::forward< Arg >( arg );
}

template< typename Arg,
          utility::Require< true, IsSorted, Arg > = true,
          utility::Require< true, utility::is_range, Range > = true >
decltype( auto ) check( Arg&& arg ){
  if( *( arg.begin() ) < 0.0 ){
    njoy::Log::error( "range is not all positive" );
    njoy::Log::info( "Non-strictly positive element ({}) found at index: {}",
                     *( arg.begin() ), 0 );
    throw exceptions::NotStrictlyPositive(
        "(sorted) range is not all strictly positive" );
  }
  return std::forward< Arg >( arg );
}
