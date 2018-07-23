auto regions( size_t index ) const {
  const auto left = index ? 
      this->interpolationParameters_.NBT()[ index -1 ] -1 : 
      0;
  const auto right = this->interpolationParameters_.NBT()[ index ];

  return
      std::make_pair( ranges::make_iterator_range
                      ( this->energies_.begin() + left,
                        this->energies_.begin() + right ),
                      ranges::make_iterator_range
                      ( this->nubar_.begin() + left,
                        this->nubar_.begin() + right ) );
}

auto regions() const{
  return
    ranges::view::iota( 0ul, this->interpolationParameters_.size() )
    | ranges::view::transform( [this ]( int i ){ return this->regions(i); } );
}