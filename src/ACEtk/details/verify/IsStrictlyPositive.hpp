template< typename T, typename = void >
struct IsStrictlyPositive : std::false_type {};

template< typename T >
struct IsStrictlyPositive< T, 
  std::enable_if_t< utility::is_range< T >::value and 
                    std::decay_t< T >::isStrictlyPositive > 
                > : std::true_type
{};

