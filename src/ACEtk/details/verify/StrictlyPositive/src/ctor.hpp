template< typename Arg = std::initializer_list< typename Range::value_type >,
          utility::Require< false, IsStrictlyPositive, Arg > = true,
          utility::Require< true, utility::is_range, Arg > = true,
          utility::Require< true, std::is_constructible, Range, Arg > = true
        >
StrictlyPositive( Arg&& arg ) :
  Range( check( std::forward< Arg >( arg ) ) )
{ }

template< typename... Args, 
          utility::Require< true, std::is_constructible, Range, Args... > = true
        >
StrictlyPositive( Args&&... args ) :
  Range( std::forward< Args >( args )... )
{ 
  check( *this );
}

template< typename Arg = std::initializer_list< typename Range::value_type >,
          utility::Require< false, IsStrictlyPositive, Arg > = true,
          utility::Require< true, IsSorted, Arg > = true,
          utility::Require< true, utility::is_range, Arg > = true,
          utility::Require< true, std::is_constructible, Range, Arg > = true
        >
StrictlyPositive( Sorted< Arg >&& arg ) :
  Range( check( std::forward< Arg >( arg ) ) )
{ }

template< typename Arg, 
          utility::Require< true, IsStrictlyPositive, Arg > = true
        >
StrictlyPositive( Arg&& arg ) :
  Range( std::forward< Arg >( arg ) )
{ }

