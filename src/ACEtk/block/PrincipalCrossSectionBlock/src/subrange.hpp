auto subrange( unsigned int i ) const {

  return this->XSS( 1 + i * this->nes_, this->nes_ );
}
