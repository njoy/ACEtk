void generateBlocks() {

  std::size_t nr = static_cast< std::size_t >( this->IXSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
  auto begin = this->begin();
  auto incident = begin + 2 * nr + 1;
  auto bins = incident + ne + 1;
  auto end = this->end();

  this->interpolation_ = block::InterpolationData( this->name(),
                                                   begin, incident );
  this->energies_ = block::details::ColumnData( this->name(),
                                                incident, bins, 1 );

  for ( unsigned int index = 1; index <= ne; ++index ) {

    this->bins_.emplace_back( this->incidentEnergy( index ),
                              bins + 1 + this->NET() * ( index - 1 ),
                              bins + 1 + this->NET() * index );
  }
}
