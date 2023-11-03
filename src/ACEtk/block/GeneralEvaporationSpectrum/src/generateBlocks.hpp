void generateBlocks() {

  std::size_t nr = static_cast< std::size_t >( this->IXSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
  auto begin = this->begin();
  auto bins = begin + 2 * nr + 2 * ne + 2;
  auto end = this->end();

  this->tabulated_ = base::TabulatedData( this->name(), begin, bins );
  this->bins_ = base::ColumnData( this->name(), bins, end, 1 );
}
