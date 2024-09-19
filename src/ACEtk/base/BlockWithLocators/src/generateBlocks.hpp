// The generateData function can be overriden in the Derived class to handle
// more complex cases involving variants. If overriding the generateData
// function does not handle the entire situation, overriding the generateBlocks
// directly is also possible.
void generateBlocks() {

  this->data_.clear();

  for ( unsigned int index = 1; index <= this->N(); ++index ) {

    // data : one-based index to the start of the data block
    // data + locator - 1 : one-based index to the start of cross section data
    std::size_t data = std::distance( this->begin(), this->iter() ) + 1;
    std::size_t locator = this->LLOC( index );
    const auto left = this->iterator( data + locator - 1 );
    const auto right = index == this->N()
                       ? this->end()
                       : this->iterator( data + this->LLOC( index + 1 ) - 1 );
    this->data_.emplace_back( Derived::generateData( locator, left, right ) );
  }
}
