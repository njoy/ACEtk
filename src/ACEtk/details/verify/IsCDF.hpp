template< typename T, typename = void >
struct IsCDF : std::false_type {};

template< typename T >
struct IsCDF< T,
                 std::enable_if_t< utility::is_range< T >::value
                                   and std::decay_t< T >::isPositive
                                   and std::decay_t< T >::isSorted > >
  : std::true_type {};

