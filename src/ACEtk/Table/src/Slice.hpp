using Slice = decltype( std::declval< const Data >().XSS( 1, 2 ) );
using Pizza = ranges::slice_view< Table::Slice >;

static Slice slice( const std::vector< double >& S ){ 
  return { S.begin(), S.end() }; 
}

template< typename Range,
          typename iterator = typename std::decay_t< Range >::iterator,
          utility::Require< true, std::is_constructible, Slice, 
                            iterator, iterator > = true
        >
static Slice slice( Range&& S ){ return { S.begin(), S.end() }; }
