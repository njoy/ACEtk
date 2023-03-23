void generateBlocks() {

  std::size_t nr = static_cast< std::size_t >( this->XSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 ) );
  auto begin = this->begin();
  auto data = begin + 2 * nr + 1;
  auto end = data + + 2 * ne + 1;

  this->interpolation_ = block::InterpolationData( std::string( this->name() ),
                                                   begin, data );
  this->data_ = block::details::ColumnData( std::string( this->name() ),
                                            data, end, 2 );
}
