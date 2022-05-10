void generateBlocks() {

  std::size_t nr = static_cast< std::size_t >( this->IXSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
  auto begina = this->begin();
  auto beginb = begina + 2 * nr + 2 * ne + 2;
  std::size_t distance = std::distance( begina, beginb );
  nr = static_cast< std::size_t >( this->IXSS( distance + 1 ) );
  ne = static_cast< std::size_t >( this->IXSS( distance + 1 + 2 * nr + 1 ) );
  auto end = beginb + 2 * nr + 2 * ne + 2;

  this->a_ = block::ParameterData( begina, beginb );
  this->b_ = block::ParameterData( beginb, end );
}
