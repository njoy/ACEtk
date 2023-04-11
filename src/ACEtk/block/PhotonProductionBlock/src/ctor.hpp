private:

/**
 *  @brief Private constructor
 */
PhotonProductionBlock( std::vector< double >&& production,
                       std::size_t nes ) :
  Base( "GPD", std::move( production ) ),
  nes_( nes ) {}

public:

  PhotonProductionBlock() = default;

  PhotonProductionBlock( const PhotonProductionBlock& ) = default;
  PhotonProductionBlock( PhotonProductionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] production    the total photon production cross section values
 */
PhotonProductionBlock( std::vector< double > production ) :
  PhotonProductionBlock( std::move( production ), production.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] gpd   the begin iterator of the GPD block in the XSS array
 *  @param[in] end   the end iterator of the GPD block in the XSS array
 *  @param[in] nes   the number of energy points
 */
PhotonProductionBlock( Iterator gpd, Iterator end, unsigned int nes ) :
  Base( "GPD", gpd, end ), nes_( nes ) {

  verifySize( this->begin(), this->end(), this->nes_ );
}

PhotonProductionBlock& operator=( const PhotonProductionBlock& ) = default;
PhotonProductionBlock& operator=( PhotonProductionBlock&& ) = default;
