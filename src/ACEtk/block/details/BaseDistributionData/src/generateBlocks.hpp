void generateBlocks( const std::string& name ) {

  auto begin = this->begin();
  auto data = inter + 2 * static_cast< unsigned int >( *begin ) + 1;

  this->interpolation_ = block::InterpolationData( name, begin, data );
  this->data_ = block::details::ColumnData( name, data, this->end(), 2 );
}
