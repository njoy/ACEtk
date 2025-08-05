BremsstrahlungHighFrequencyBlock() = default;

BremsstrahlungHighFrequencyBlock( const BremsstrahlungHighFrequencyBlock& ) = default;
BremsstrahlungHighFrequencyBlock( BremsstrahlungHighFrequencyBlock&& ) = default;

BremsstrahlungHighFrequencyBlock& operator=( const BremsstrahlungHighFrequencyBlock& ) = default;
BremsstrahlungHighFrequencyBlock& operator=( BremsstrahlungHighFrequencyBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies         the energy values
 *  @param[in] crosssections    the high-frequency-limit cross section values
 */
BremsstrahlungHighFrequencyBlock( std::vector< double > energies,
                                  std::vector< double > crosssections ) :
  ArrayData( "HFB",
             std::move( energies ), std::move( crosssections ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the HFB block in the XSS array
 *  @param[in] end     the end iterator of the HFB block in the XSS array
 *  @param[in] nhfb    the number of energy points
 */
BremsstrahlungHighFrequencyBlock( Iterator begin, Iterator end, unsigned int nhfb ) :
  ArrayData( "HFB", begin, end, nhfb, 2 ) {}
