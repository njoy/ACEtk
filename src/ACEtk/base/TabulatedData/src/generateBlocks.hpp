void generateBlocks() {

  const auto nr = static_cast< std::size_t >( this->IXSS( 1 ) );
  const auto ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
  const auto begin = this->begin();
  const auto data = begin + 2 * nr + 1;
  const auto end = data + 2 * ne + 1;

  this->interpolation_ = block::InterpolationData( this->name(), begin, data );
  this->data_ = ColumnData( this->name(), data, end, 2 );
}
