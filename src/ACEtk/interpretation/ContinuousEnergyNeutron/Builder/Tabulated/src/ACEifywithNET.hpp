void ACEifywithNET( Table::Data& tData ){
  decltype( auto ) xss = tData.XSS();

  if( bool( this->parameters ) ){
    decltype( auto ) p = parameters.value();
    xss.push_back( p.first.size() );
    xss |= ranges::action::push_back( p.first );
    xss |= ranges::action::push_back( p.second );
  }
  else{
    xss.push_back( 0 );
  }

  xss.push_back( x.size() );
  xss |= ranges::action::push_back( x );

  xss.push_back( this->y.front().size() );
  details::ACEify( tData, this->y );

}
