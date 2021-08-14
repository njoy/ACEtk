void generateBlocks() {

  auto begin = this->begin();
  auto inter = begin + 1;
  auto data = inter + 2 * static_cast< unsigned int >( *inter ) + 1;

  this->interpolation_ = block::InterpolationData( "NU::TABLE", inter, data );
  this->data_ = block::ColumnData( "NU::TABLE", data, this->end(), 2 );
}
