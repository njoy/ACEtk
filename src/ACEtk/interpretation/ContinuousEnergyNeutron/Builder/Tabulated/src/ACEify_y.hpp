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

template< typename U=T,
          utility::Require< true, utility::is_range, U > = true >
void ACEify_y( Table::Data& tData ){
  auto& xss = tData.XSS();

  for( auto Y : this->y ){
    xss |= ranges::action::push_back( Y );
  }
}

template< typename... R >
void ACEify_y( Table::Data& tData, R... ){

  tData.XSS() |= ranges::action::push_back( this->y );
}
