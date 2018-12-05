template< typename T, typename = void >
struct IsPositive : std::false_type {};

template< typename T >
struct IsPositive< T, 
  std::enable_if_t< utility::is_range< T >::value and 
                    std::decay_t< T >::positive > 
                > : std::true_type
{};

