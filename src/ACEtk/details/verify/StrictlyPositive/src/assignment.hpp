template< typename Arg = std::initializer_list< utility::value_t< Range > >,
          utility::Require< false, IsStrictlyPositive, Arg > = true,
          utility::Require< true, std::is_assignable, Range, Arg > = true,
          utility::Require< true, std::is_constructible, Range, Arg > = true
        >
StrictlyPositive& operator=( Arg arg ){
  static_cast< Range& >( *this ) = check( std::forward< Arg >( arg ) );
  return *this;
}

template< typename Arg,
          utility::Require< true, IsStrictlyPositive, Arg > = true,
          utility::Require< false, std::is_assignable, Range&, Arg > = true
        >
StrictlyPositive& operator=( Arg&& arg ){
  static_cast< Range& >( *this ) = check( std::forward< Arg >( arg ) );
  return *this;
}
