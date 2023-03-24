EquiprobableOutgoingEnergyBins() = default;

EquiprobableOutgoingEnergyBins( const EquiprobableOutgoingEnergyBins& ) = default;
EquiprobableOutgoingEnergyBins( EquiprobableOutgoingEnergyBins&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident   the incident energy value
 *  @param[in] energies   the outgoing energy values
 */
EquiprobableOutgoingEnergyBins( double incident,
                                std::vector< double >&& energies ) :
  Base( "DLW::EquiprobableOutgoingEnergyBins", std::move( energies ) ),
  incident_( incident ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] incident   the incident energy value
 *  @param[in] begin      the begin iterator of the equiprobable bin data
 *  @param[in] end        the end iterator of the equiprobable bin data
 */
EquiprobableOutgoingEnergyBins( double incident, Iterator begin, Iterator end ) :
  Base( "DLW::EquiprobableOutgoingEnergyBins", begin, end ),
  incident_( incident ) {}

EquiprobableOutgoingEnergyBins& operator=( const EquiprobableOutgoingEnergyBins& ) = default;
EquiprobableOutgoingEnergyBins& operator=( EquiprobableOutgoingEnergyBins&& ) = default;
