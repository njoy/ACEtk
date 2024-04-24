void generateBlocks() {

  const auto nr = static_cast< std::size_t >( this->IXSS( 1 ) );
  const auto ne = static_cast< std::size_t >( this->IXSS( 2 + 2 * nr ) );
  auto begin = this->begin();
  auto data = this->iterator( 2 + 2 * nr );
  auto end = this->iterator( 2 + 2 * nr + 2 * ne + 1 );

  this->interpolation_ = continuous::InterpolationData( this->name(), begin, data );
  this->values_ = ColumnData( this->name(), data, end, 2 );
  for ( unsigned int index = 1; index <= this->numberValues(); ++index ) {

    const double value = this->value( 1, index );
    const auto locb = this->distributionLocator( index );
    const auto locator = this->relativeDistributionLocator( index );
    const auto left = this->iterator( locator );
    auto right = this->end();
    for ( auto next = index + 1; next <= this->numberValues(); ++next ) {

      auto nextlocator = this->relativeDistributionLocator( next );
      if ( nextlocator > locator ) {

        right = this->iterator( nextlocator );
        break;
      }
    }
    this->distributions_.emplace_back( Distribution( value, locb, left, right ) );
  }
}
