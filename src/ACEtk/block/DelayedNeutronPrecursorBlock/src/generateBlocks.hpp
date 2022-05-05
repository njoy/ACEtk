void generateBlocks() {

  auto left = this->begin();
  auto right = this->begin();
  for ( unsigned int index = 1; index <= this->NPCR(); ++index ) {

    std::size_t nr = static_cast< std::size_t >( round( *( left + 1 ) ) );
    std::size_t ne = static_cast< std::size_t >( round( *( left + 1 + 2 * nr + 1 ) ) );
    right = left + 2 + 2 * nr + 2 * ne + 1;
    this->data_.emplace_back( left, right );
    left = right;
  }
}
