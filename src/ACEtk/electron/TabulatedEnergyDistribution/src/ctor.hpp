TabulatedEnergyDistribution() = default;

TabulatedEnergyDistribution( const TabulatedEnergyDistribution& ) = default;
TabulatedEnergyDistribution( TabulatedEnergyDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy      the associated energy value
 *  @param[in] outgoing    the outgoing energy values (LB values)
 *  @param[in] cdf         the cdf values (LB values)
 */
TabulatedEnergyDistribution( double energy,
                             std::vector< double > outgoing,
                             std::vector< double > cdf ) :
  ArrayData( "TabulatedEnergyDistribution",
             std::move( outgoing ), std::move( cdf ) ),
  energy_( energy ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] energy    the associated energy value
 *  @param[in] begin     the begin iterator of the tabulated distribution data
 *  @param[in] end       the end iterator of the tabulated distribution data
 *  @param[in] lb        the number of outgoing energy values
 */
TabulatedEnergyDistribution( double energy,
                             Iterator begin, Iterator end,
                             unsigned int la ) :
  ArrayData( "TabulatedEnergyDistribution", begin, end, la, 2 ),
  energy_( energy ) {}

TabulatedEnergyDistribution& operator=( const TabulatedEnergyDistribution& ) = default;
TabulatedEnergyDistribution& operator=( TabulatedEnergyDistribution&& ) = default;
