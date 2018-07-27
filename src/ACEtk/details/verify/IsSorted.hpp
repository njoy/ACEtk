template< typename T, typename = void >
struct IsSorted : std::false_type {};

template< typename T >
struct IsSorted< T,
                 std::enable_if_t< utility::is_range< T >::value
                                   and std::decay_t< T >::isSorted > >
  : std::true_type {};
