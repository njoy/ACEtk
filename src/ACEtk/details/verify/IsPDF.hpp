template< typename T, typename = void >
struct IsPDF : std::false_type {};

template< typename T >
struct IsPDF< T,
                 std::enable_if_t< utility::is_range< T >::value
                                   and std::decay_t< T >::isPDF > >
  : std::true_type {};
