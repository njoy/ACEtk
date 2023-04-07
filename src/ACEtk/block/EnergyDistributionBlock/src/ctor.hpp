private:

/**
 *  @brief Private constructor
 */
EnergyDistributionBlock( std::vector< DistributionData >&& distributions,
                          std::size_t nr ) :
  Base( "DLW", generateXSS( std::move( distributions ) ) ),
  nr_( nr ) {

  this->dlw_ = this->begin() + this->nr_;
}

public:

EnergyDistributionBlock() = default;

EnergyDistributionBlock( const EnergyDistributionBlock& ) = default;
EnergyDistributionBlock( EnergyDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
EnergyDistributionBlock( std::vector< DistributionData > distributions ) :
  EnergyDistributionBlock( std::move( distributions ),
                           distributions.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] ldlw    the begin iterator of the LDLW block in the XSS array
 *  @param[in] dlw     the begin iterator of the DLW block in the XSS array
 *  @param[in] end     the end iterator of the DLW block in the XSS array
 *  @param[in] nr      the number of reactions producing the projectile
 *                     (excluding elastic)
 */
EnergyDistributionBlock( Iterator ldlw, Iterator dlw, Iterator end,
                         unsigned int nr ) :
  Base( "DLW", ldlw, end ), nr_( nr ), dlw_( dlw ) {

  verifySize( this->begin(), this->dlw_, this->end(), this->nr_ );
}

EnergyDistributionBlock& operator=( const EnergyDistributionBlock& ) = default;
EnergyDistributionBlock& operator=( EnergyDistributionBlock&& ) = default;
