IncidentParticleGroupStructureBlock() = default;

IncidentParticleGroupStructureBlock( const IncidentParticleGroupStructureBlock& ) = default;
IncidentParticleGroupStructureBlock( IncidentParticleGroupStructureBlock&& ) = default;

IncidentParticleGroupStructureBlock& operator=( const IncidentParticleGroupStructureBlock& ) = default;
IncidentParticleGroupStructureBlock& operator=( IncidentParticleGroupStructureBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] groupMeans         the mean energies of each group in MeV
 *  @param[in] groupWidths        the widths of each group in MeV
 */
IncidentParticleGroupStructureBlock( std::vector< double > groupMeans, std::vector< double > groupWidths ) :
  ArrayData( "ERG",
             std::move( groupMeans ), std::move( groupWidths ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the ERG block in the XSS array
 *  @param[in] end     the end iterator of the ERG block in the XSS array
 *  @param[in] nes     the number of energy groups
 */
IncidentParticleGroupStructureBlock( Iterator begin, Iterator end, unsigned int nes ) :
  ArrayData( "ERG", begin, end, nes, 2 ) {}
