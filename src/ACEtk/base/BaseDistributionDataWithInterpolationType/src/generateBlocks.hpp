void generateBlocks() {

  std::size_t ne = static_cast< std::size_t >( this->IXSS( 2 ) );
  auto data = this->iterator( 2 );
  auto end = this->iterator( 2 + 2 * ne + 1 );

  this->values_ = block::details::ColumnData( std::string( this->name() ),
                                              data, end, 2 );
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
