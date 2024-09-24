TabulatedEnergyDistribution() = default;

TabulatedEnergyDistribution( const TabulatedEnergyDistribution& ) = default;
TabulatedEnergyDistribution( TabulatedEnergyDistribution&& ) = default;

TabulatedEnergyDistribution& operator=( const TabulatedEnergyDistribution& ) = default;
TabulatedEnergyDistribution& operator=( TabulatedEnergyDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident        the incident energy or cosine value
 *  @param[in] interpolation   the interpolation type
 *  @param[in] outgoing        the outgoing energy values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 *  @param[in] discrete        the number discrete photon lines (defaults to 0)
 */
TabulatedEnergyDistribution( double incident,
                             int interpolation,
                             std::vector< double > outgoing,
                             std::vector< double > pdf,
                             std::vector< double > cdf,
                             std::size_t discrete = 0 ) :
  TabulatedProbabilityDistribution(
        "TabulatedEnergyDistribution",
        discrete * 10 + interpolation, std::move( outgoing ),
        std::move( pdf ), std::move( cdf ), {} ),
  incident_( incident ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] incident   the incident energy value
 *  @param[in] begin      the begin iterator of the tabulated distribution data
 *  @param[in] end        the end iterator of the tabulated distribution data
 */
TabulatedEnergyDistribution( double incident, Iterator begin, Iterator end ) :
  TabulatedProbabilityDistribution( "TabulatedEnergyDistribution",
                                    begin, end ),
  incident_( incident ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] incident   the incident energy value
 *  @param[in] locb       the starting xss index with respect to the superblock
 *  @param[in] begin      the begin iterator of the tabulated distribution data
 *  @param[in] end        the end iterator of the tabulated distribution data
 */
TabulatedEnergyDistribution( double incident, std::size_t,
                             Iterator begin, Iterator end ) :
  TabulatedEnergyDistribution( incident, begin, end ) {}
