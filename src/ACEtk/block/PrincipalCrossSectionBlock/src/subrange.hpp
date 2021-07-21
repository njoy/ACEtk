auto subrange( unsigned int i ) const {

  const auto left = std::next( this->begin(), i * this->nes_ );
  const auto right = left + this->nes_;
  return ranges::make_iterator_range( left, right );
}
