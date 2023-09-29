void generateBlocks() {

  auto begin = this->begin();
  auto iter = std::next( begin, 3 * this->N() );
  this->information_ = ArrayData( "ELAS", begin, iter, this->N(), 3 );

  std::size_t data = std::distance( begin, iter ) + 1;
  for ( unsigned int index = 1; index <= this->N(); ++index ) {

    std::size_t locator = this->LLOC( index );
    const auto left = this->iterator( data + locator - 1 );
    const auto right = std::next( left, 2 * this->length( index ) );
    this->data_.emplace_back( this->energy( index ), left, right, this->length( index ) );
  }
}
