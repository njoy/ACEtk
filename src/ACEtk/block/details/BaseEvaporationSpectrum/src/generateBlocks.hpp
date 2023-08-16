void generateBlocks() {

  std::size_t nr = static_cast< std::size_t >( round( this->IXSS( 1 ) ) );
  std::size_t ne = static_cast< std::size_t >( round( this->IXSS( 1 + 2 * nr + 1 ) ) );
  auto begin = this->begin();
  auto end = begin + 2 * nr + 2 * ne + 2;

  this->tabulated_ = block::details::BaseTabulatedData( this->name(), begin, end );
}
