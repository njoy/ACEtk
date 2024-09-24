TabulatedProbabilityDistribution() = default;

TabulatedProbabilityDistribution( const TabulatedProbabilityDistribution& ) = default;
TabulatedProbabilityDistribution( TabulatedProbabilityDistribution&& ) = default;

TabulatedProbabilityDistribution& operator=( const TabulatedProbabilityDistribution& ) = default;
TabulatedProbabilityDistribution& operator=( TabulatedProbabilityDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] name            the name of the block
 *  @param[in] interpolation   the interpolation type
 *  @param[in] values          the values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 *  @param[in] data            the additional data (arrays of N values)
 */
TabulatedProbabilityDistribution( std::string name,
                                  int interpolation,
                                  std::vector< double > values,
                                  std::vector< double > pdf,
                                  std::vector< double > cdf,
                                  std::vector< std::vector< double > > data ) :
  Base( std::move( name ),
        generateXSS( interpolation,
                     std::move( values ), std::move( pdf ), std::move( cdf ),
                     std::move( data ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name            the name of the block
 *  @param[in] interpolation   the interpolation type
 *  @param[in] values          the values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 */
TabulatedProbabilityDistribution( std::string name,
                                  int interpolation,
                                  std::vector< double > values,
                                  std::vector< double > pdf,
                                  std::vector< double > cdf ) :
  TabulatedProbabilityDistribution(
      std::move( name ), interpolation,
      std::move( values ), std::move( pdf ), std::move( cdf ), {} ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin      the begin iterator of the tabulated distribution data
 *  @param[in] end        the end iterator of the tabulated distribution data
 */
TabulatedProbabilityDistribution( std::string name, Iterator begin, Iterator end ) :
  Base( std::move( name ), begin, end ) {

  verifySize( this->begin(), this->end(), this->numberValues() );
}
