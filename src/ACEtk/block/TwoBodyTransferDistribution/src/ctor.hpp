TwoBodyTransferDistribution() = default;

TwoBodyTransferDistribution( const TwoBodyTransferDistribution& ) = default;
TwoBodyTransferDistribution( TwoBodyTransferDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 *  @param[in] c1      the value of C1
 *  @param[in] c2      the value of C2
 */
TwoBodyTransferDistribution( double emin, double emax, double c1, double c2 ) :
  TwoParameterDistribution( "TwoBodyTransferDistribution", emin, emax, c1, c2 ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the block
 *  @param[in] end     the end iterator of the block
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 */
TwoBodyTransferDistribution( Iterator begin, Iterator end,
                             double emin, double emax ) :
  TwoParameterDistribution( "TwoBodyTransferDistribution", begin, end, emin, emax ) {}

TwoBodyTransferDistribution& operator=( const TwoBodyTransferDistribution& ) = default;
TwoBodyTransferDistribution& operator=( TwoBodyTransferDistribution&& ) = default;
