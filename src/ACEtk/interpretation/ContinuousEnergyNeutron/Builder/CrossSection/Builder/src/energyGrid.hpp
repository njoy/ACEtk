Derived& energyGrid( Table::pizza energyGrid ){
  this->energyGrid_ = 
      details::verify::sorted( details::verify::positive( energyGrid ) );
  return static_cast< Derived& >( *this );
}

decltype(auto) energyGrid( Table::Slice energyGrid ){
  return this->energyGrid( 
    energyGrid | ranges::view::slice( 0l, ranges::distance( energyGrid ) ) );
}
