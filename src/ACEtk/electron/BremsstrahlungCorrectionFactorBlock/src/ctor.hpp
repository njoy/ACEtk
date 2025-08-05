BremsstrahlungCorrectionFactorBlock() = default;

BremsstrahlungCorrectionFactorBlock( const BremsstrahlungCorrectionFactorBlock& ) = default;
BremsstrahlungCorrectionFactorBlock( BremsstrahlungCorrectionFactorBlock&& ) = default;

BremsstrahlungCorrectionFactorBlock& operator=( const BremsstrahlungCorrectionFactorBlock& ) = default;
BremsstrahlungCorrectionFactorBlock& operator=( BremsstrahlungCorrectionFactorBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies       the energy values
 *  @param[in] corrections    the correction factor values
 */
BremsstrahlungCorrectionFactorBlock( std::vector< double > energies,
                                     std::vector< double > corrections ) :
  ArrayData( "CRB",
             std::move( energies ), std::move( corrections ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the CRB block in the XSS array
 *  @param[in] end     the end iterator of the CRB block in the XSS array
 *  @param[in] ncrb    the number of energy points
 */
BremsstrahlungCorrectionFactorBlock( Iterator begin, Iterator end, unsigned int ncrb ) :
  ArrayData( "CRB", begin, end, ncrb, 2 ) {}
