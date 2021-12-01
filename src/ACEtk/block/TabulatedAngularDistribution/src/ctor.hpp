TabulatedAngularDistribution() = default;

TabulatedAngularDistribution( const TabulatedAngularDistribution& ) = default;
TabulatedAngularDistribution( TabulatedAngularDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy          the associated energy value
 *  @param[in] interpolation   the interpolation type
 *  @param[in] cosines         the cosine values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 */
TabulatedAngularDistribution( double energy,
                              int interpolation,
                              std::vector< double > cosines,
                              std::vector< double > pdf,
                              std::vector< double > cdf ) :
  TabulatedProbabilityDistribution(
        "TabulatedAngularDistribution",
        interpolation, std::move( cosines ),
        std::move( pdf ), std::move( cdf ), {} ),
  energy_( energy ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] energy     the associated energy value
 *  @param[in] begin      the begin iterator of the tabulated distribution data
 *  @param[in] end        the end iterator of the tabulated distribution data
 */
TabulatedAngularDistribution( double energy, Iterator begin, Iterator end ) :
  TabulatedProbabilityDistribution( "TabulatedAngularDistribution",
                                    begin, end ),
  energy_( energy ) {}

TabulatedAngularDistribution& operator=( const TabulatedAngularDistribution& ) = default;
TabulatedAngularDistribution& operator=( TabulatedAngularDistribution&& ) = default;
