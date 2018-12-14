template< typename Arg = Range,
          utility::Require< true, std::is_assignable, Range&, Arg > = true >
Normal& operator=( Arg&& arg ){
  static_cast< Range& >( *this ) = check( std::forward< Arg >( arg ) );
  return *this;
}

