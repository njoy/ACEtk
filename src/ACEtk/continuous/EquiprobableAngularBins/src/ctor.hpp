EquiprobableAngularBins() = default;

EquiprobableAngularBins( const EquiprobableAngularBins& ) = default;
EquiprobableAngularBins( EquiprobableAngularBins&& ) = default;

EquiprobableAngularBins& operator=( const EquiprobableAngularBins& ) = default;
EquiprobableAngularBins& operator=( EquiprobableAngularBins&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy     the associated energy value
 *  @param[in] cosines    the cosine values (33 values)
 */
EquiprobableAngularBins( double energy, std::vector< double > cosines ) :
  Base( "EquiprobableAngularBins", std::move( cosines ) ),
  energy_( energy ) {

  verifySize( this->XSS().size() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] energy     the associated energy value
 *  @param[in] begin      the begin iterator of the equiprobable bin data
 *  @param[in] end        the end iterator of the equiprobable bin data
 */
EquiprobableAngularBins( double energy, Iterator begin, Iterator end ) :
  Base( "EquiprobableAngularBins", begin, end ),
  energy_( energy ) {

  verifySize( this->begin(), this->end() );
}
