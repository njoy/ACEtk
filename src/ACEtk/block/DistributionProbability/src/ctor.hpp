DistributionProbability() = default;

DistributionProbability( const DistributionProbability& ) = default;
DistributionProbability( DistributionProbability&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] energies         the energy values
 *  @param[in] probabilities    the probability values values
 */
DistributionProbability( std::vector< long >&& boundaries,
                         std::vector< long >&& interpolants,
                         std::vector< double >&& energies,
                         std::vector< double >&& probabilities ) :
  BaseTabulatedData( "DLW::DistributionProbability",
                     std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( probabilities ) ) {}

/**
 *  @brief Constructor (linear interpolation is assumed)
 *
 *  @param[in] energies         the energy values
 *  @param[in] probabilities    the probability values values
 */
DistributionProbability( std::vector< double >&& energies,
                         std::vector< double >&& probabilities ) :
  DistributionProbability( {}, {}, std::move( energies ),
                           std::move( probabilities ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
DistributionProbability( Iterator begin, Iterator end ) :
  BaseTabulatedData( "DLW::DistributionProbability", begin, end ) {}

DistributionProbability& operator=( const DistributionProbability& ) = default;
DistributionProbability& operator=( DistributionProbability&& ) = default;
