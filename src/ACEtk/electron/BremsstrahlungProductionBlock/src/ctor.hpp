BremsstrahlungProductionBlock() = default;

BremsstrahlungProductionBlock( const BremsstrahlungProductionBlock& ) = default;
BremsstrahlungProductionBlock( BremsstrahlungProductionBlock&& ) = default;

BremsstrahlungProductionBlock& operator=( const BremsstrahlungProductionBlock& ) = default;
BremsstrahlungProductionBlock& operator=( BremsstrahlungProductionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] electronenergies    the electron energy points
 *  @param[in] photonratios        the photon energy ratio points
 *  @param[in] crosssections       the bremsstrahlung cross section values
 */
BremsstrahlungProductionBlock( std::vector< double > electronenergies,
                               std::vector< double > photonratios,
                               std::vector< std::vector< double > > crosssections ) :
  MatrixData( "XSB",
              std::move( electronenergies ), std:move( photonratios ),
              std::move( crosssections ), false ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin       the begin iterator of the XSB block in the XSS array
 *  @param[in] end         the end iterator of the XSB block in the XSS array
 *  @param[in] neb         the number of electron energies
 *  @param[in] npb         the number of photon energy ratios
 */
BremsstrahlungProductionBlock( Iterator begin,
                               Iterator end,
                               unsigned int neb,
                               unsigned int npb ) :
  MatrixData( "XSB", begin, end, neb, npb, false ) {}
