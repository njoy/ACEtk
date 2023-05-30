static EnergyDistributionData
generateData( std::size_t locator, Iterator left, Iterator right ) {

  // left points to the LNW value - single law if zero
  unsigned int lnw = static_cast< unsigned int >( round( *left ) );
  if ( lnw == 0 ) {

    EnergyDistributionType law = static_cast< EnergyDistributionType >( round( *( left + 1 ) ) );
    std::size_t idat = static_cast< std::size_t >( round( *( left + 2 ) ) );
    std::size_t nr = static_cast< std::size_t >( round( *( left + 3 ) ) );
    std::size_t ne = static_cast< std::size_t >( round( *( left + 3 + 2 * nr + 1 ) ) );
    double emin = *( left + 3 + 2 * nr + 1 + 1 );
    double emax = *( left + 3 + 2 * nr + 1 + ne );

    // compute iterators into the xss array
    const auto start = left + idat - locator;

    // switch on the law and return the appropriate data
    switch ( law ) {

      case EnergyDistributionType::DiscretePhoton : {

        return DiscretePhotonDistribution( start, right, emin, emax );
      }
      case EnergyDistributionType::LevelScattering : {

        return LevelScatteringDistribution( start, right, emin, emax );
      }
      case EnergyDistributionType::TwoBodyTransfer : {

        return TwoBodyTransferDistribution( start, right, emin, emax );
      }
      case EnergyDistributionType::NBodyPhaseSpace : {

        return NBodyPhaseSpaceDistribution( start, right, emin, emax );
      }
      case EnergyDistributionType::TabulatedEnergy : {

        return OutgoingEnergyDistributionData( idat, start, right );
      }
      case EnergyDistributionType::KalbachMann : {

        return KalbachMannDistributionData( idat, start, right );
      }
      case EnergyDistributionType::TabulatedEnergyAngle : {

        return EnergyAngleDistributionData( idat, start, right );
      }
      case EnergyDistributionType::TabulatedAngleEnergy : {

        return AngleEnergyDistributionData( idat, start, right );
      }
      case EnergyDistributionType::Equiprobable : {

        return EquiprobableOutgoingEnergyBinData( start, right );
      }
      case EnergyDistributionType::GeneralEvaporation : {

        return GeneralEvaporationSpectrum( start, right );
      }
      case EnergyDistributionType::SimpleMaxwellianFission : {

        return SimpleMaxwellianFissionSpectrum( start, right );
      }
      case EnergyDistributionType::Evaporation : {

        return EvaporationSpectrum( start, right );
      }
      case EnergyDistributionType::Watt : {

        return EnergyDependentWattSpectrum( start, right );
      }
      default : {

        throw std::runtime_error( "DLW law currently not implemented: "
                                  + std::to_string( static_cast< short >( law ) ) );
      }
    }
  }
  else {

    return MultiDistributionData( locator, left, right );
  }
}

void generateBlocks() {

  for ( unsigned int index = 1; index <= this->NR(); ++index ) {

    // data : one-based index to the start of the data block
    // data + locator - 1 : one-based index to the start of cross section data
    std::size_t data = std::distance( this->begin(), this->iter() ) + 1;
    std::size_t locator = this->LDLW( index );
    std::size_t multiplicity = index == this->NR()
                               ? 0
                               : this->TYR().multiplicity( index + 1 );
    const auto left = this->iterator( data + locator - 1 );
    const auto right = index == this->NR()
                       ? this->end()
                       : multiplicity < 100
                           ? this->iterator( data + this->LDLW( index + 1 ) - 1 )
                           : this->iterator( data + multiplicity - 100 - 1 );
    this->data_.emplace_back( generateData( locator, left, right ) );
    multiplicity = this->TYR().multiplicity( index );
    if ( multiplicity > 100 ) {

      auto mleft = this->iterator( data + multiplicity - 100 - 1 );
      this->multiplicities_.emplace_back( TabulatedMultiplicity( mleft, left ) );
    }
    else {

      this->multiplicities_.emplace_back( static_cast< unsigned int >( multiplicity ) );
    }
  }
  this->frames_.insert( this->frames_.end(),
                        this->TYR().referenceFrames().begin(),
                        this->TYR().referenceFrames().begin() + this->NR() );
}
