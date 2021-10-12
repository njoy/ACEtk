EquiprobableAngularBins() = default;

EquiprobableAngularBins( const EquiprobableAngularBins& ) = default;
EquiprobableAngularBins( EquiprobableAngularBins&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident   the incident energy value
 *  @param[in] values     the cosine values (33 values)
 */
EquiprobableAngularBins( double incident, std::vector< double >&& cosines ) :
  Base( "AND::EquiprobableAngularBins", std::move( cosines ) ),
  incident_( incident ) {

  verifySize( this->XSS().size() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the equiprobable bin data
 *  @param[in] end      the end iterator of the equiprobable bin data
 */
EquiprobableAngularBins( Iterator begin, Iterator end, double incident ) :
  Base( "AND::EquiprobableAngularBins", begin, end ),
  incident_( incident ) {

  verifySize( this->begin(), this->end() );
}

EquiprobableAngularBins& operator=( const EquiprobableAngularBins& ) = default;
EquiprobableAngularBins& operator=( EquiprobableAngularBins&& ) = default;
