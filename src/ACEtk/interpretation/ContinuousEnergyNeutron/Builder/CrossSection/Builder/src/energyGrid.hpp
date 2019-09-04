Builder& energyGrid( Table::pizza energyGrid ){
  this->energyGrid_ = 
      details::verify::positive( details::verify::sorted( energyGrid ) );
  return *this;
}

decltype(auto) energyGrid( Table::Slice energyGrid ){
  return this->energyGrid( 
    energyGrid | ranges::view::slice( 0l, ranges::distance( energyGrid ) ) );
}
