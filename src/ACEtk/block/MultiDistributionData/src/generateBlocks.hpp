void generateBlocks() {

  std::size_t locator = 1; // this->locb_ - ( this->locb_ - 1 )
  std::size_t lnw = 0;
  do {

    // lnw, law and idat from xss array (one based index starting at locb)
    lnw = static_cast< std::size_t >( this->IXSS( locator ) );
    EnergyDistributionType law =
        static_cast< EnergyDistributionType >( this->IXSS( locator + 1 ) );
    std::size_t idat = static_cast< std::size_t >( this->IXSS( locator + 2 ) );

    // iterators into the xss array (zero based index into internal xss array)
    auto pbegin = this->begin() + locator + 3 - 1;
    auto dbegin = this->begin() + idat - ( this->locb_ - 1 ) - 1;
    auto end = lnw ? this->begin() + lnw - ( this->locb_ - 1 ) - 1 : this->end();

    // add the probabilities to the xss array
    this->probabilities_.emplace_back( pbegin, dbegin );
    double emin = this->probabilities_.back().energies().front();
    double emax = this->probabilities_.back().energies().back();

    // add the actual distribution
    switch ( law ) {

      case EnergyDistributionType::DiscretePhoton : {

        this->distributions_.emplace_back(
            DiscretePhotonDistribution( dbegin, end, emin, emax ) );
        break;
      }
      case EnergyDistributionType::LevelScattering : {

        this->distributions_.emplace_back(
            LevelScatteringDistribution( dbegin, end, emin, emax ) );
        break;
      }
      case EnergyDistributionType::NBodyPhaseSpace : {

        this->distributions_.emplace_back(
            NBodyPhaseSpaceDistribution( dbegin, end, emin, emax ) );
        break;
      }
      case EnergyDistributionType::TwoBodyTransfer : {

        this->distributions_.emplace_back(
            TwoBodyTransferDistribution( dbegin, end, emin, emax ) );
        break;
      }
      case EnergyDistributionType::TabulatedEnergy : {

        this->distributions_.emplace_back(
            OutgoingEnergyDistributionData( idat, dbegin, end ) );
        break;
      }
      case EnergyDistributionType::KalbachMann : {

        this->distributions_.emplace_back(
            KalbachMannDistributionData( idat, dbegin, end ) );
        break;
      }
      case EnergyDistributionType::TabulatedEnergyAngle : {

        this->distributions_.emplace_back(
          EnergyAngleDistributionData( idat, dbegin, end ) );
        break;
      }
      case EnergyDistributionType::TabulatedAngleEnergy : {

        this->distributions_.emplace_back(
          AngleEnergyDistributionData( idat, dbegin, end ) );
      }
      case EnergyDistributionType::Equiprobable : {

        this->distributions_.emplace_back(
            EquiprobableOutgoingEnergyBinData( dbegin, end ) );
        break;
      }
      case EnergyDistributionType::GeneralEvaporation : {

        this->distributions_.emplace_back(
            GeneralEvaporationSpectrum( dbegin, end ) );
        break;
      }
      case EnergyDistributionType::SimpleMaxwellianFission : {

        this->distributions_.emplace_back(
            SimpleMaxwellianFissionSpectrum( dbegin, end ) );
        break;
      }
      case EnergyDistributionType::Evaporation : {

        this->distributions_.emplace_back(
            EvaporationSpectrum( dbegin, end ) );
        break;
      }
      case EnergyDistributionType::Watt : {

        this->distributions_.emplace_back(
            EnergyDependentWattSpectrum( dbegin, end ) );
        break;
      }
      default : {

        throw std::runtime_error( "DLW law currently not implemented: "
                                  + std::to_string( static_cast< short >( law ) ) );
      }
    }

    locator = lnw - ( this->locb_ - 1 );
  }
  while ( lnw != 0 );
}
