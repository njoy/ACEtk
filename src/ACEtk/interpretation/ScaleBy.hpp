template< typename T >
class ScaleBy{
  T scalar;
public:
  ScaleBy( T scalar ) : scalar(scalar) {}

  template<typename Range>
  auto operator()( Range&& range ) const {
    return range 
      | ranges::view::transform( 
          [ scalar_ = this->scalar ](auto&& value){ return value * scalar_; } );
  }
};

template<typename T>
constexpr auto scaleBy(T value){ return ScaleBy<T>{value}; }
