template< typename T, typename = void >
struct IsNormal : std::false_type {};

template< typename T >
struct IsNormal< T,
                 std::enable_if_t< utility::is_range< T >::value
                                   and std::decay_t< T >::isNormal > >
  : std::true_type {};
