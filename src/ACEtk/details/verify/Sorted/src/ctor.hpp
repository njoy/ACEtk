template< typename Arg = std::initializer_list< typename Range::value_type >,
          utility::Require< false, IsSorted, Arg > = true,
          utility::Require< true, utility::is_range, Arg > = true,
          utility::Require< true, std::is_constructible, Range, Arg > = true
        >
Sorted( Arg&& arg ) :
  Range( check( std::forward< Arg >( arg ) ) )
{ }

template< typename... Args, 
          utility::Require< true, std::is_constructible, Range, Args... > = true
        >
Sorted( Args&&... args ):
  Range( check( std::forward< Args >( args )... ) )
{ }

template< typename Arg,
          utility::Require< true, IsSorted, Arg > = true,
          utility::Require< true, std::is_constructible, Range, Arg > = true 
        >
Sorted( Arg&& arg ) :
  Range( std::forward< Arg >( arg ) )
{ }

