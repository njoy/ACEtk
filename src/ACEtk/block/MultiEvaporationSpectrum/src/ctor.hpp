MultiEvaporationSpectrum() = default;

MultiEvaporationSpectrum( const MultiEvaporationSpectrum& base ) = default;
MultiEvaporationSpectrum( MultiEvaporationSpectrum&& base ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] probabilities    the probabilities
 *  @param[in] distributions    the distributions
 */
MultiEvaporationSpectrum( std::vector< DistributionProbability > probabilities,
                          std::vector< EvaporationSpectrum > distributions,
                          std::size_t locb = 1 ) :
  MultiDistribution( "MultiEvaporationSpectrum",
                      std::move( probabilities ), std::move( distributions ),
                      locb ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the block in the XSS array
 *  @param[in] end      the end iterator of the block in the XSS array
 */
MultiEvaporationSpectrum( std::size_t locb, Iterator begin, Iterator end ) :
  MultiDistribution( "MultiEvaporationSpectrum", locb, begin, end ) {}

MultiEvaporationSpectrum& operator=( const MultiEvaporationSpectrum& base ) = default;
MultiEvaporationSpectrum& operator=( MultiEvaporationSpectrum&& base ) = default;
