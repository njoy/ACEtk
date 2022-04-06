EnergyDistributionBlock() = default;

EnergyDistributionBlock( const EnergyDistributionBlock& ) = default;
EnergyDistributionBlock( EnergyDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] distributions    the energy distribution data
 */
EnergyDistributionBlock(
    std::vector< EnergyDistributionData > distributions ) :
  BaseBlockWithLocators( "DLW", std::move( distributions ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] ldlw    the begin iterator of the LDLW block in the XSS array
 *  @param[in] dlw     the begin iterator of the DLW block in the XSS array
 *  @param[in] end     the end iterator of the DLW block in the XSS array
 *  @param[in] nr      the number of reactions
 */
EnergyDistributionBlock(
    Iterator lsig, Iterator sig, Iterator end,
    unsigned int nr ) :
  BaseBlockWithLocators( "DLW", lsig, sig, end, nr ) {}

EnergyDistributionBlock& operator=( const EnergyDistributionBlock& ) = default;
EnergyDistributionBlock& operator=( EnergyDistributionBlock&& ) = default;
