void generateBlocks() {

  for ( unsigned int index = 1; index <= this->NTR(); ++index ) {

    // sig : one-based index to the start of the SIG block
    // sig + locator - 1 : one-based index to the start of cross section data
    std::size_t sig = std::distance( this->begin(), this->sig_ ) + 1;
    const auto left = this->iterator( sig + this->LSIG( index ) - 1 );
    const auto right = index == this->NTR()
                       ? this->end()
                       : this->iterator( sig + this->LSIG( index + 1 ) - 1 );
    this->xs_.emplace_back( Derived::generateData( left, right ) );
  }
}
