void generateBlocks() {

  std::size_t ne = static_cast< std::size_t >( this->XSS( 2 ) );
  auto data = this->begin() + 1;
  auto end = data + 4 * ne + 1;

  this->values_ = block::details::ColumnData( std::string( this->name() ),
                                              data, end, 4 );
  for ( unsigned int index = 1; index <= this->values_.N(); ++index ) {

    const double energy = this->values_.value( 1, index );
    const double probability = this->values_.value( 2, index );
    const double cumulative = this->values_.value( 3, index );
    const auto locb = this->distributionLocator( index );
    const auto locator = this->relativeDistributionLocator( index );
    const auto left = std::next( this->begin(), locator - 1 );
    const auto right = index == this->numberValues()
                       ? this->end()
                       : std::next( this->begin(),
                         this->relativeDistributionLocator( index + 1 ) - 1 );
    this->distributions_.emplace_back(
      TabulatedAngularDistributionWithProbability( energy, probability,
                                                   cumulative, left, right ) );
  }
}
