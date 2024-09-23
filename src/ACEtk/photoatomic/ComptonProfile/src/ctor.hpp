ComptonProfile() = default;

ComptonProfile( const ComptonProfile& ) = default;
ComptonProfile( ComptonProfile&& ) = default;

ComptonProfile& operator=( const ComptonProfile& ) = default;
ComptonProfile& operator=( ComptonProfile&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] interpolation   the interpolation type
 *  @param[in] momentum        the cosine values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 */
ComptonProfile( int interpolation,
                           std::vector< double > momentum,
                           std::vector< double > pdf,
                           std::vector< double > cdf ) :
  TabulatedProbabilityDistribution(
        "ComptonProfile", interpolation, std::move( momentum ),
        std::move( pdf ), std::move( cdf ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin      the begin iterator of the tabulated distribution data
 *  @param[in] end        the end iterator of the tabulated distribution data
 */
ComptonProfile( Iterator begin, Iterator end ) :
  TabulatedProbabilityDistribution( "ComptonProfile", begin, end ) {}
