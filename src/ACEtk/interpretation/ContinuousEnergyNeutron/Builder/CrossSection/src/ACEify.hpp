void ACEify( Table::Data& tData ) {
  decltype( auto ) grid = this->energyGrid.base();
  auto IE = ranges::distance( grid.begin(), this->energyGrid.begin() ) + 1;

  tData.XSS().push_back( IE );
  tData.XSS().push_back( this->values.size() );
  tData.XSS() |= ranges::action::push_back( values );
}
