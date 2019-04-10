template< typename U, typename =void >
struct hasACEify : std::false_type {};

template< typename U >
struct hasACEify< U,
          utility::void_t<
            decltype(
              std::declval< U >().ACEify( std::declval< Table::Data& >() )
            )
          >
        > : std::true_type
{};

template< typename U=T, 
          utility::Require< true, hasACEify, U > = true 
        >
void ACEify_y( Table::Data& tData ){
  auto& xss = tData.XSS();

  for( auto& ele : this->y ){
    ele.ACEify( tData );
  }
}

template< typename U=T,
          utility::Require< true, std::is_convertible, U, double > = true
        >
void ACEify_y( Table::Data& tData ){
  tData.XSS() |= ranges::action::push_back( this-> y );
}

template< typename U=T,
          utility::Require< false, hasACEify, U > = true,
          utility::Require< true, utility::is_range, U > = true
        >
void ACEify_y( Table::Data& tData ){
  auto& xss = tData.XSS();

  for( auto Y : this->y ){
    xss |= ranges::action::push_back( Y );
  }
}
