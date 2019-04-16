template< typename U=T, 
          utility::Require< true, details::hasACEify, U > = true 
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
          utility::Require< false, details::hasACEify, U > = true,
          utility::Require< true, utility::is_range, U > = true
        >
void ACEify_y( Table::Data& tData ){
  auto& xss = tData.XSS();

  for( auto Y : this->y ){
    xss |= ranges::action::push_back( Y );
  }
}
