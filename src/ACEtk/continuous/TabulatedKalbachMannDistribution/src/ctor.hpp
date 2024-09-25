TabulatedKalbachMannDistribution() = default;

TabulatedKalbachMannDistribution( const TabulatedKalbachMannDistribution& ) = default;
TabulatedKalbachMannDistribution( TabulatedKalbachMannDistribution&& ) = default;

TabulatedKalbachMannDistribution& operator=( const TabulatedKalbachMannDistribution& ) = default;
TabulatedKalbachMannDistribution& operator=( TabulatedKalbachMannDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident        the incident energy value
 *  @param[in] interpolation   the interpolation type
 *  @param[in] cosines         the cosine values (N values)
 *  @param[in] pdf             the pdf values (N values)
 *  @param[in] cdf             the cdf values (N values)
 *  @param[in] r               the precompound fraction values (N values)
 *  @param[in] a               the cdf values (N values)
 *  @param[in] discrete        the number discrete photon lines (defaults to 0)
 */
TabulatedKalbachMannDistribution( double incident,
                                  int interpolation,
                                  std::vector< double > cosines,
                                  std::vector< double > pdf,
                                  std::vector< double > cdf,
                                  std::vector< double > r,
                                  std::vector< double > a,
                                  std::size_t discrete = 0 ) :
  TabulatedProbabilityDistribution(
        "TabulatedKalbachMannDistribution",
        discrete * 10 + interpolation, std::move( cosines ),
        std::move( pdf ), std::move( cdf ), { std::move( r ), std::move( a ) } ),
  incident_( incident ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] incident   the incident energy value
 *  @param[in] begin      the begin iterator of the tabulated distribution data
 *  @param[in] end        the end iterator of the tabulated distribution data
 */
TabulatedKalbachMannDistribution( double incident, Iterator begin, Iterator end ) :
  TabulatedProbabilityDistribution( "TabulatedKalbachMannDistribution",
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
TabulatedKalbachMannDistribution( double incident, std::size_t,
                                  Iterator begin, Iterator end ) :
  TabulatedKalbachMannDistribution( incident, begin, end ) {}
