template< typename Arg,
          utility::Require< false, IsSorted, Arg > = true,
          utility::Require< true, std::is_assignable, Range&, Arg > = true
        >
Sorted& operator=( Arg&& arg ){
  check( arg );
  static_cast< Range& >( *this ) = check( std::forward< Arg >( arg ) );
  return *this;
}

template< typename Arg,
          utility::Require< true, IsSorted, Arg > = true,
          utility::Require< true, std::is_assignable, Range&, Arg > = true
        >
Sorted& operator=( Arg&& arg ){
  static_cast< Range& >( *this ) = std::forward< Arg >( arg );
  return *this;
}
