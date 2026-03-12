BremsstrahlungEnergySpectrumBlock() = default;

BremsstrahlungEnergySpectrumBlock( const BremsstrahlungEnergySpectrumBlock& ) = default;
BremsstrahlungEnergySpectrumBlock( BremsstrahlungEnergySpectrumBlock&& ) = default;

BremsstrahlungEnergySpectrumBlock& operator=( const BremsstrahlungEnergySpectrumBlock& ) = default;
BremsstrahlungEnergySpectrumBlock& operator=( BremsstrahlungEnergySpectrumBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energyratios    the photon energy ratios
 */
BremsstrahlungEnergySpectrumBlock( std::vector< double > energyratios ) :
  ArrayData( "RKT",
             std::vector< std::vector< double > > { energyratios } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the RKT block in the XSS array
 *  @param[in] end     the end iterator of the RKT block in the XSS array
 *  @param[in] nrkt    the number of photon energy ratios
 */
BremsstrahlungEnergySpectrumBlock( Iterator begin, Iterator end, unsigned int nrkt ) :
  ArrayData( "RKT", begin, end, nrkt, 1 ) {}
