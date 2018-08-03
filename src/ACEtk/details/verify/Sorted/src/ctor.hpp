template< typename Arg = Range,
          utility::Require< true, std::is_constructible, Range, Arg > = true >
Sorted( Arg&& arg ) : Range( check( std::forward< Arg >( arg ) ) ){}

template< typename... Args,
          utility::Require< true,
                            std::is_constructible,
                            Range, Args... > = true >
Sorted( Args&&... args ) : Range( std::forward< Args >( args )... ){
  check( *this );
}

