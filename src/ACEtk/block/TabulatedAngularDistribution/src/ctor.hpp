TabulatedAngularDistribution() = default;

TabulatedAngularDistribution( const TabulatedAngularDistribution& ) = default;
TabulatedAngularDistribution( TabulatedAngularDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident        the incident energy value
 *  @param[in] interpolation   the interpolation type
 *  @param[in] cosines         the cosine values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 */
TabulatedAngularDistribution( double incident,
                              int interpolation,
                              std::vector< double >&& cosines,
                              std::vector< double >&& pdf,
                              std::vector< double >&& cdf ) :
  TabulatedProbabilityDistribution(
        "AND::TabulatedAngularDistribution",
        interpolation, std::move( cosines ),
        std::move( pdf ), std::move( cdf ), {} ),
  incident_( incident ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] incident   the incident energy value
 *  @param[in] begin      the begin iterator of the tabulated distribution data
 *  @param[in] end        the end iterator of the tabulated distribution data
 */
TabulatedAngularDistribution( double incident, Iterator begin, Iterator end ) :
  TabulatedProbabilityDistribution( "AND::TabulatedAngularDistribution",
                                    begin, end ),
  incident_( incident ) {}

TabulatedAngularDistribution& operator=( const TabulatedAngularDistribution& ) = default;
TabulatedAngularDistribution& operator=( TabulatedAngularDistribution&& ) = default;
