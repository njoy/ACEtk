ElectronTabulatedAngularDistribution() = default;

ElectronTabulatedAngularDistribution( const ElectronTabulatedAngularDistribution& ) = default;
ElectronTabulatedAngularDistribution( ElectronTabulatedAngularDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy          the associated energy value
 *  @param[in] cosines         the cosine values (LA values)
 *  @param[in] cdf             the cdf values (LA values)
 */
ElectronTabulatedAngularDistribution( double energy,
                                      std::vector< double > cosines,
                                      std::vector< double > cdf ) :
  ArrayData( "ElectronTabulatedAngularDistribution",
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
ElectronTabulatedAngularDistribution( double energy,
                                      Iterator begin, Iterator end,
                                      unsigned int la ) :
  ArrayData( "ElectronTabulatedAngularDistribution", begin, end, la, 2 ),
  energy_( energy ) {}

ElectronTabulatedAngularDistribution& operator=( const ElectronTabulatedAngularDistribution& ) = default;
ElectronTabulatedAngularDistribution& operator=( ElectronTabulatedAngularDistribution&& ) = default;
