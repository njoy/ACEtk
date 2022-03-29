TabulatedAngularDistributionWithProbability() = default;

TabulatedAngularDistributionWithProbability( const TabulatedAngularDistributionWithProbability& ) = default;
TabulatedAngularDistributionWithProbability( TabulatedAngularDistributionWithProbability&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy          the associated energy value
 *  @param[in] probability     the associated probability value
 *  @param[in] cumulative      the associated cumulative probability value
 *  @param[in] interpolation   the interpolation type
 *  @param[in] cosines         the cosine values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 */
TabulatedAngularDistributionWithProbability( double energy,
                                             double probability,
                                             double cumulative,
                                             int interpolation,
                                             std::vector< double > cosines,
                                             std::vector< double > pdf,
                                             std::vector< double > cdf ) :
  TabulatedAngularDistribution( energy, interpolation, std::move( cosines ),
                                std::move( pdf ), std::move( cdf ) ),
  pdf_( probability ), cdf_( cumulative ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] energy         the associated energy value
 *  @param[in] probability    the associated probability value
 *  @param[in] cumulative     the associated cumulative probability value
 *  @param[in] begin          the begin iterator of the tabulated distribution data
 *  @param[in] end            the end iterator of the tabulated distribution data
 */
TabulatedAngularDistributionWithProbability( double energy,
                                             double probability,
                                             double cumulative,
                                             Iterator begin,
                                             Iterator end ) :
  TabulatedAngularDistribution( energy, begin, end ),
  pdf_( probability ), cdf_( cumulative ) {}

TabulatedAngularDistributionWithProbability& operator=( const TabulatedAngularDistributionWithProbability& ) = default;
TabulatedAngularDistributionWithProbability& operator=( TabulatedAngularDistributionWithProbability&& ) = default;
