void generateBlocks() {

  auto nb = this->NB();
  auto ne = this->NE();

  auto begin = this->begin();
  auto inter = begin + 1;
  auto data = int + 2 * nb;

  this->interpolation_ = block::InterpolationData( "NU::TABLE", inter, data );
  this->data_ = block::ColumnData( "NU::TABLE", data, end );
}
