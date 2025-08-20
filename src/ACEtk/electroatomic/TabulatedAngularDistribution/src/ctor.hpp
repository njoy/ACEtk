TabulatedAngularDistribution() = default;

TabulatedAngularDistribution( const TabulatedAngularDistribution& ) = default;
TabulatedAngularDistribution( TabulatedAngularDistribution&& ) = default;

TabulatedAngularDistribution& operator=( const TabulatedAngularDistribution& ) = default;
TabulatedAngularDistribution& operator=( TabulatedAngularDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy          the associated energy value
 *  @param[in] cosines         the cosine values (LA values)
 *  @param[in] cdf             the cdf values (LA values)
 */
TabulatedAngularDistribution( double energy,
                              std::vector< double > cosines,
                              std::vector< double > cdf ) :
  ArrayData( "TabulatedAngularDistribution",
             std::move( cosines ), std::move( cdf ) ),
  energy_( energy ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] energy    the associated energy value
 *  @param[in] begin     the begin iterator of the tabulated distribution data
 *  @param[in] end       the end iterator of the tabulated distribution data
 *  @param[in] la        the number of cosine values
 */
TabulatedAngularDistribution( double energy,
                              Iterator begin, Iterator end,
                              unsigned int la ) :
  ArrayData( "TabulatedAngularDistribution", begin, end, la, 2 ),
  energy_( energy ) {}
