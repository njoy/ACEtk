BremsstrahlungAngularSpectrumBlock() = default;

BremsstrahlungAngularSpectrumBlock( const BremsstrahlungAngularSpectrumBlock& ) = default;
BremsstrahlungAngularSpectrumBlock( BremsstrahlungAngularSpectrumBlock&& ) = default;

BremsstrahlungAngularSpectrumBlock& operator=( const BremsstrahlungAngularSpectrumBlock& ) = default;
BremsstrahlungAngularSpectrumBlock& operator=( BremsstrahlungAngularSpectrumBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energyratios    the photon energy ratios
 */
BremsstrahlungAngularSpectrumBlock( std::vector< double > energyratios ) :
  ArrayData( "RKA", std::move( energyratios ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the RKA block in the XSS array
 *  @param[in] end     the end iterator of the RKA block in the XSS array
 *  @param[in] nrka    the number of photon energy ratios
 */
BremsstrahlungAngularSpectrumBlock( Iterator begin, Iterator end, unsigned int nrka ) :
  ArrayData( "RKA", begin, end, nrka, 1 ) {}
