auto ACEify() const{
  std::vector< double > aced;
  aced.emplace_back( 2 );

  if( parameters ){
    auto p = parameters.value();
    aced 
      |= ranges::action::push_back( 
          ranges::view::concat(
            ranges::view::single( p.first.size() ), p.first, p.second
          )
        );
  }
  else{
    aced |= ranges::action::push_back( ranges::view::single( 0 ) );
  }

  aced 
    |= ranges::action::push_back( 
      ranges::view::concat( ranges::view::single( x.size() ), x )
      );

  return aced |= ranges::action::push_back( this->ACEify_y( ) );

}
