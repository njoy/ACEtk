void generateBlocks() {

  auto nb = this->NB();
  auto ne = this->NE();

  auto begin = this->begin();
  auto inter = begin + 1;
  auto data = inter + 2 * nb;

  this->interpolation_ = block::InterpolationData( "NU::TABLE", inter, data );
  this->data_ = block::ColumnData( "NU::TABLE", data, this->end(), 2 );
}
