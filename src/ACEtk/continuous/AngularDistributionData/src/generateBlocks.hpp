void generateBlocks() {

  this->distributions_.clear();

  std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 ) );
  auto begin = this->begin();
  auto end = this->iterator( 2 * ne + 2 );

  this->values_ = base::ColumnData( this->name(), begin, end, 2 );
  for ( unsigned int index = 1; index <= this->numberIncidentEnergies(); ++index ) {

    const auto type = this->distributionType( index );
    const double incident = this->incidentEnergy( index );
    if ( type == AngularDistributionType::Isotropic ) {

      this->distributions_.emplace_back( IsotropicAngularDistribution( incident ) );
    }
    else {

      const auto locator = this->relativeDistributionLocator( index );
      const auto left = this->iterator( locator );
      auto right = this->end();
      for ( auto next = index + 1; next <= this->numberIncidentEnergies(); ++next ) {

        auto nextlocator = this->relativeDistributionLocator( next );
        if ( nextlocator > locator ) {

          right = this->iterator( nextlocator );
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
