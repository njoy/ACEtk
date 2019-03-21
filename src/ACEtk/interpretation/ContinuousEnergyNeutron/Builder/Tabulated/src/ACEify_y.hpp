template< typename U=T, 
          typename = utility::void_t< 
            decltype( 
              std::declval< 
                ranges::value_type_t< std::decay_t< U > > 
              >().ACEify()
            )
          >
>
auto ACEify_y(){
  return this->y 
    | ranges::view::for_each(
        []( auto& ele ){ return ele.ACEify(); }
      );
}

template< typename... R >
auto ACEify_y( R... ){

  return this->y | ranges::view::all;
}
