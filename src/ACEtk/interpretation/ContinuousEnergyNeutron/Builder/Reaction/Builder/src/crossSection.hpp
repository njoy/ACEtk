Builder& crossSection( std::vector< double >&& xs, Slice energyGrid ){

  try{
    details::verify::equalSize( xs, energyGrid );
    this->crossSection_ = std::move( xs );
    this->energyGrid_ = energyGrid;
    return *this;

  } catch( std::range_error& e){
    throw;
  }
}

Builder& crossSection( std::vector< double >&& xs ){
  return crossSection( std::move( xs ), this->parent.get().energyGrid() );
}

