void generateBlocks() {

  for ( unsigned int index = this->zero_index_ ? 0 : 1;
        index <= this->NR(); ++index ) {

    if ( this->isGiven( index ) ) {

      if ( this->isFullyIsotropic( index ) ) {

        this->data_.emplace_back( block::FullyIsotropicDistribution() );
      }
      else {

        // xand : one-based index to the start of the AND block
        // xand + locator - 1 : one-based index to the start of distribution data
        const std::size_t xand = std::distance( this->begin(), this->iterator_ ) + 1;
        const std::size_t land = this->LAND( index );
        const std::size_t locator = xand + land - 1;
        const auto left = this->iterator( locator );
        auto right = this->end();
        for ( auto next = index + 1; next <= this->NR(); ++next ) {

          const auto nextlocator = xand + this->LAND( next ) - 1;
          if ( nextlocator > locator ) {

            right = this->iterator( nextlocator );
            break;
          }
        }
        this->data_.emplace_back( block::AngularDistributionData( land, left, right ) );
      }
    }
    else {

      this->data_.emplace_back( block::DistributionGivenElsewhere() );
    }
  }
}
