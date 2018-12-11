Derived& energyGrid( Slice energyGrid ){
  this->energyGrid_ = energyGrid;
  return static_cast< Derived& >( *this );
}
