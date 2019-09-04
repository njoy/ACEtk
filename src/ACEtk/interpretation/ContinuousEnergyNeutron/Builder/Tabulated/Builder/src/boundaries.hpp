template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Derived& boundaries( Range&& boundaries ){
  this->boundaries_ = std::move( 
      details::verify::strictlyPositive( 
        details::verify::sorted( boundaries ) ) );
  return static_cast< Derived& >( *this );
}
