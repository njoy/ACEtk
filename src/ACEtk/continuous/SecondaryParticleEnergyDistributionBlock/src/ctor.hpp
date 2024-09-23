SecondaryParticleEnergyDistributionBlock() = default;

SecondaryParticleEnergyDistributionBlock(
    const SecondaryParticleEnergyDistributionBlock& base ) :
  BlockWithLocators( base ),
  tyrh_( base.tyrh_ ),
  frames_( base.frames_ ) {

  if ( Base::owner() ) {

    this->generateFrames();
  }
}

SecondaryParticleEnergyDistributionBlock(
    SecondaryParticleEnergyDistributionBlock&& base ) :
  BlockWithLocators( std::move( base ) ),
  tyrh_( std::move( base.tyrh_ ) ),
  frames_( std::move( base.frames_ ) ) {

  if ( Base::owner() ) {

    this->generateFrames();
  }
}

SecondaryParticleEnergyDistributionBlock& operator=( const SecondaryParticleEnergyDistributionBlock& base ) {

  if ( this != &base ) {

    BlockWithLocators::operator=( base );
    this->tyrh_ = base.tyrh_;
    this->frames_ = base.frames_;
    if ( Base::owner() ) {

      this->generateFrames();
    }
  }
  return *this;
}

SecondaryParticleEnergyDistributionBlock& operator=( SecondaryParticleEnergyDistributionBlock&& base ) {

  if ( this != &base ) {

    BlockWithLocators::operator=( std::move( base ) );
    this->tyrh_ = std::move( base.tyrh_ );
    this->frames_ = std::move( base.frames_ );
    if ( Base::owner() ) {

      this->generateFrames();
    }
  }
  return *this;
}

/**
 *  @brief Constructor (without reference frames for DLWH)
 *
 *  @param[in] distributions    the energy distribution data
 */
SecondaryParticleEnergyDistributionBlock(
    std::vector< EnergyDistributionData > distributions ) :
  BlockWithLocators( "DLWH", std::move( distributions ) ), tyrh_( std::nullopt ) {

  this->generateFrames();
}

/**
 *  @brief Constructor (with reference frames for DLWH)
 *
 *  @param[in] distributions    the energy distribution data
 *  @param[in] frames           the reference frames
 */
SecondaryParticleEnergyDistributionBlock(
    std::vector< EnergyDistributionData > distributions,
    std::vector< ReferenceFrame > frames ) :
  BlockWithLocators( "DLWH", std::move( distributions ) ), tyrh_( std::move( frames ) ) {

  this->generateFrames();
}

/**
 *  @brief Constructor (without reference frames for DLWH)
 *
 *  @param[in] ldlw    the begin iterator of the LDLW block in the XSS array
 *  @param[in] dlw     the begin iterator of the DLW block in the XSS array
 *  @param[in] end     the end iterator of the DLW block in the XSS array
 *  @param[in] nr      the number of reactions
 */
SecondaryParticleEnergyDistributionBlock(
    Iterator lsig, Iterator sig, Iterator end, unsigned int nr ) :
  BlockWithLocators( "DLWH", lsig, sig, end, nr ), tyrh_( std::nullopt ) {

  this->generateFrames();
}

/**
 *  @brief Constructor (with reference frames for DLWH)
 *
 *  @param[in] ldlw    the begin iterator of the LDLW block in the XSS array
 *  @param[in] dlw     the begin iterator of the DLW block in the XSS array
 *  @param[in] end     the end iterator of the DLW block in the XSS array
 *  @param[in] tyrh    the associated DLW block
 *  @param[in] nr      the number of reactions
 */
SecondaryParticleEnergyDistributionBlock(
    Iterator lsig, Iterator sig, Iterator end,
    continuous::TYRH tyrh, unsigned int nr ) :
  BlockWithLocators( "DLWH", lsig, sig, end, nr ), tyrh_( std::move( tyrh ) ) {

  this->generateFrames();
}
