void generateBlocks() {

  auto begin = this->begin();
  auto left = begin;
  auto right = begin;
  std::size_t locator = 1;
  for ( unsigned int index = 1; index <= this->NPCR(); ++index ) {

    std::size_t nr = static_cast< std::size_t >( this->IXSS( locator + 1 ) );
    std::size_t ne = static_cast< std::size_t >( this->IXSS( locator + 1 + 2 * nr + 1 ) );
    locator += 2 + 2 * nr + 2 * ne + 1;
    right = begin + locator - 1;
    this->data_.emplace_back( left, right, index );
    left = right;
  }
}
