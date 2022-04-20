ThermalScatteringEquiprobableAngularBins() = default;

ThermalScatteringEquiprobableAngularBins( const ThermalScatteringEquiprobableAngularBins& ) = default;
ThermalScatteringEquiprobableAngularBins( ThermalScatteringEquiprobableAngularBins&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy     the outgoing energy value
 *  @param[in] cosines    the cosine values
 */
ThermalScatteringEquiprobableAngularBins( double energy,
                                          std::vector< double > cosines ) :
  Base( "ThermalScatteringEquiprobableAngularBins",
        generateXSS( energy, std::move( cosines ) ) ),
  nbins_( cosines.size() - 1 ) {

  verifySize( this->XSS().size(), this->numberBins() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] nbins      the number of bins
 *  @param[in] begin      the begin iterator of the equiprobable bin data
 *  @param[in] end        the end iterator of the equiprobable bin data
 */
ThermalScatteringEquiprobableAngularBins( std::size_t nbins,
                                          Iterator begin, Iterator end ) :
  Base( "ThermalScatteringEquiprobableAngularBins", begin, end ),
  nbins_( nbins ) {

  verifySize( this->begin(), this->end(), this->numberBins() );
}

ThermalScatteringEquiprobableAngularBins& operator=( const ThermalScatteringEquiprobableAngularBins& ) = default;
ThermalScatteringEquiprobableAngularBins& operator=( ThermalScatteringEquiprobableAngularBins&& ) = default;
