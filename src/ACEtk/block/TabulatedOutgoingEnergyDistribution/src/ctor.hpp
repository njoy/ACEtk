TabulatedOutgoingEnergyDistribution() = default;

TabulatedOutgoingEnergyDistribution( const TabulatedOutgoingEnergyDistribution& ) = default;
TabulatedOutgoingEnergyDistribution( TabulatedOutgoingEnergyDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident        the incident energy value
 *  @param[in] interpolation   the interpolation type
 *  @param[in] cosines         the cosine values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 *  @param[in] discrete        the number discrete photon lines (defaults to 0)
 */
TabulatedOutgoingEnergyDistribution( double incident,
                                     int interpolation,
                                     std::vector< double > cosines,
                                     std::vector< double > pdf,
                                     std::vector< double > cdf,
                                     std::size_t discrete = 0 ) :
  TabulatedProbabilityDistribution(
        "TabulatedOutgoingEnergyDistribution",
        discrete * 10 + interpolation, std::move( cosines ),
        std::move( pdf ), std::move( cdf ), {} ),
  incident_( incident ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] incident   the incident energy value
 *  @param[in] begin      the begin iterator of the tabulated distribution data
 *  @param[in] end        the end iterator of the tabulated distribution data
 */
TabulatedOutgoingEnergyDistribution( double incident,
                                     Iterator begin, Iterator end ) :
  TabulatedProbabilityDistribution( "TabulatedOutgoingEnergyDistribution",
                                    begin, end ),
  incident_( incident ) {}

TabulatedOutgoingEnergyDistribution& operator=( const TabulatedOutgoingEnergyDistribution& ) = default;
TabulatedOutgoingEnergyDistribution& operator=( TabulatedOutgoingEnergyDistribution&& ) = default;
