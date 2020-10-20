template< typename T, typename = void >
struct IsCosineBins : std::false_type {};

template< typename T >
struct IsCosineBins< T,
                 std::enable_if_t< utility::is_range< T >::value
                                   and std::decay_t< T >::isCosineBins > >
  : std::true_type {};
