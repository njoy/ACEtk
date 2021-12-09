void generateBlocks() {

  std::size_t nr = static_cast< std::size_t >( this->XSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 ) );
  auto begin = this->begin();
  auto data = begin + 2 * nr + 1;
  auto end = data + + 2 * ne + 1;

  this->interpolation_ = block::InterpolationData( this->name(), begin, data );
  this->values_ = block::details::ColumnData( this->name(), data, end, 2 );
  for ( unsigned int index = 1; index <= this->values_.N(); ++index ) {

    const double value = this->value( index );
    const auto locb = this->distributionLocator( index );
    const auto locator = this->relativeDistributionLocator( index );
    const auto left = std::next( this->begin(), locator - 1 );
    const auto right = index == this->numberValues()
                       ? this->end()
                       : std::next( this->begin(),
                         this->relativeDistributionLocator( index + 1 ) - 1 );
    this->distributions_.emplace_back( Distribution( value, locb, left, right ) );
  }
}
