void generateBlocks() {

  auto begin = this->begin();
  auto data = begin + 2 * this->numberInterpolationRegions() + 1;
  auto end = data + + 2 * this->numberIncidentEnergies() + 1;

  this->interpolation_ = block::InterpolationData( std::string( this->name() ),
                                                   begin, data );
  this->data_ = block::details::ColumnData( std::string( this->name() ),
                                            data, end, 2 );
}
