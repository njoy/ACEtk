void generateBlocks() {

  std::size_t ne = static_cast< std::size_t >( round( this->XSS( 1 ) ) );
  auto begin = this->begin();
  auto end = begin + 2 * ne + 1;

  this->values_ = block::details::ColumnData( this->name(), begin, end, 2 );
  for ( unsigned int index = 1; index <= this->values_.N(); ++index ) {

    const auto type = this->distributionType( index );
    const double incident = this->incidentEnergy( index );
    if ( type == AngularDistributionType::Isotropic ) {

      this->distributions_.emplace_back( IsotropicAngularDistribution( incident ) );
    }
    else {

      const auto locator = this->relativeDistributionLocator( index );
      const auto left = std::next( this->begin(), locator - 1 );
      auto right = this->end();
      for ( auto next = index + 1; next <= this->numberIncidentEnergies(); ++next ) {

        auto nextlocator = this->relativeDistributionLocator( next );
        if ( nextlocator > locator ) {

          right = std::next( this->begin(), nextlocator - 1 );
          break;
        }
      }
      if ( type == AngularDistributionType::Tabulated ) {

        this->distributions_.emplace_back( TabulatedAngularDistribution( incident, left, right ) );
      }
      else {

        this->distributions_.emplace_back( EquiprobableAngularBins( incident, left, right ) );
      }
    }
  }
}
