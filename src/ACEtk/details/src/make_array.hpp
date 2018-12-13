template< size_t n >
struct make_array_fn{
  template< typename Range >
  auto operator()( Range&& range ) const {
    using T = std::decay_t< decltype( *(range.begin()) ) >;
    assert( ranges::distance( range ) == n );
    std::array< T, n > rValue;
    ranges::copy( range, rValue.begin() );
    
    return rValue;
  }
};

template< size_t n >
static constexpr auto make_array = make_array_fn< n >{};
