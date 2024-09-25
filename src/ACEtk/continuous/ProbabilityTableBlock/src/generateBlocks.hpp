void generateBlocks() {

  this->data_.clear();

  std::size_t m = this->M();
  auto left = this->begin() + 6 + this->N();
  auto right = left;
  for ( unsigned int index = 1; index <= this->N(); ++index ) {

    right = left + 6 * m;
    this->data_.emplace_back( left, right, this->XSS( 6 + index ), m );
    left = right;
  }
}
