void generateBlocks() {

  std::size_t nr = static_cast< std::size_t >( this->XSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 ) );
  auto begin = this->begin();
  auto incident = begin + 2 * nr + 1;
  auto bins = incident + ne + 1;
  auto end = this->end();

  this->interpolation_ = block::InterpolationData( std::string( this->name() ),
                                                   begin, incident );
  this->energies_ = block::details::ColumnData( std::string( this->name() ),
                                                incident, bins, 1 );
  this->bins_ = block::details::ColumnData( std::string( this->name() ),
                                            bins, end, ne );
}
