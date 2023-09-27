PhotoatomicComptonProfile() = default;

PhotoatomicComptonProfile( const PhotoatomicComptonProfile& ) = default;
PhotoatomicComptonProfile( PhotoatomicComptonProfile&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] interpolation   the interpolation type
 *  @param[in] momentum        the cosine values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 */
PhotoatomicComptonProfile( int interpolation,
                           std::vector< double > momentum,
                           std::vector< double > pdf,
                           std::vector< double > cdf ) :
  TabulatedProbabilityDistribution(
        "PhotoatomicComptonProfile", interpolation, std::move( momentum ),
        std::move( pdf ), std::move( cdf ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin      the begin iterator of the tabulated distribution data
 *  @param[in] end        the end iterator of the tabulated distribution data
 */
PhotoatomicComptonProfile( Iterator begin, Iterator end ) :
  TabulatedProbabilityDistribution( "PhotoatomicComptonProfile", begin, end ) {}

PhotoatomicComptonProfile& operator=( const PhotoatomicComptonProfile& ) = default;
PhotoatomicComptonProfile& operator=( PhotoatomicComptonProfile&& ) = default;
