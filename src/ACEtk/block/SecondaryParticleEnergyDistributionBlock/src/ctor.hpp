SecondaryParticleEnergyDistributionBlock() = default;

SecondaryParticleEnergyDistributionBlock( const SecondaryParticleEnergyDistributionBlock& ) = default;
SecondaryParticleEnergyDistributionBlock( SecondaryParticleEnergyDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] distributions    the energy distribution data
 */
SecondaryParticleEnergyDistributionBlock(
    std::vector< EnergyDistributionData > distributions ) :
  BaseBlockWithLocators( "DLWH", std::move( distributions ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] ldlw    the begin iterator of the LDLW block in the XSS array
 *  @param[in] dlw     the begin iterator of the DLW block in the XSS array
 *  @param[in] end     the end iterator of the DLW block in the XSS array
 *  @param[in] nr      the number of reactions
 */
SecondaryParticleEnergyDistributionBlock(
    Iterator lsig, Iterator sig, Iterator end,
    unsigned int nr ) :
  BaseBlockWithLocators( "DLWH", lsig, sig, end, nr ) {}

SecondaryParticleEnergyDistributionBlock& operator=( const SecondaryParticleEnergyDistributionBlock& ) = default;
SecondaryParticleEnergyDistributionBlock& operator=( SecondaryParticleEnergyDistributionBlock&& ) = default;
