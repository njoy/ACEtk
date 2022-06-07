PhotoAtomicComptonProfile() = default;

PhotoAtomicComptonProfile( const PhotoAtomicComptonProfile& ) = default;
PhotoAtomicComptonProfile( PhotoAtomicComptonProfile&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] interpolation   the interpolation type
 *  @param[in] momentum        the cosine values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 */
PhotoAtomicComptonProfile( int interpolation,
                           std::vector< double > momentum,
                           std::vector< double > pdf,
                           std::vector< double > cdf ) :
  TabulatedProbabilityDistribution(
        "PhotoAtomicComptonProfile", interpolation, std::move( momentum ),
        std::move( pdf ), std::move( cdf ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin      the begin iterator of the tabulated distribution data
 *  @param[in] end        the end iterator of the tabulated distribution data
 */
PhotoAtomicComptonProfile( Iterator begin, Iterator end ) :
  TabulatedProbabilityDistribution( "PhotoAtomicComptonProfile", begin, end ) {}

PhotoAtomicComptonProfile& operator=( const PhotoAtomicComptonProfile& ) = default;
PhotoAtomicComptonProfile& operator=( PhotoAtomicComptonProfile&& ) = default;
