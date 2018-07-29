template< typename Arg = Range,
          utility::Require< true, std::is_constructible, Range, Arg > = true >
StrictlyPositive( Arg&& arg ) : Range( check( std::forward< Arg >( arg ) ) ) {}

template< typename... Args,
          utility::Require< true,
                            std::is_constructible,
                            Range, Args... > = true >
StrictlyPositive( Args&&... args ) : Range( std::forward< Args >( args )... ) {
  check( *this );
}
