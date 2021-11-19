void generateBlocks() {

  std::size_t nr = static_cast< std::size_t >( this->XSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 ) );
  auto begin = this->begin();
  auto bins = begin + 2 * nr + 2 * ne + 2;
  auto end = this->end();

  this->tabulated_ = block::details::BaseTabulatedData( std::string( this->name() ),
                                                        begin, bins );
  this->bins_ = block::details::ColumnData( std::string( this->name() ),
                                            bins, end, 1 );
}
