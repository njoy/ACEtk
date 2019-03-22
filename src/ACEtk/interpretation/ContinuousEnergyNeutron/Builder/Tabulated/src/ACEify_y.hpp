template< typename U=T, 
          typename = utility::void_t< 
            decltype( 
              std::declval< 
                ranges::value_type_t< std::decay_t< U > > 
              >().ACEify()
            )
          >
>
void ACEify_y( Table::Data& tData ){
  auto& xss = tData.XSS();
    xss |= ranges::view::for_each(
        [ &tData ]( auto& ele ){ return ele.ACEify( tData ); }
      );
}

template< typename... R >
void ACEify_y( Table::Data& tData, R... ){

  tData.XSS() |= ranges::action::push_back( this->y );
}
