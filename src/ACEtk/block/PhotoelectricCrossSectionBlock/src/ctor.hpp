PhotoelectricCrossSectionBlock() = default;

PhotoelectricCrossSectionBlock( const PhotoelectricCrossSectionBlock& ) = default;
PhotoelectricCrossSectionBlock( PhotoelectricCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] photoelectric    the photoelectric cross section values
 *                              for each shell
 */
PhotoelectricCrossSectionBlock(
    std::vector< std::vector< double > > electroionisation ) :
  ArrayData( "SPHEL", std::move( electroionisation ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the SPHEL block in the XSS array
 *  @param[in] end     the end iterator of the SPHEL block in the XSS array
 *  @param[in] nssh    the number of electron shells
 *  @param[in] nes     the number of energy values
 */
PhotoelectricCrossSectionBlock( Iterator begin, Iterator end,
                                unsigned int nssh, unsigned int nes ) :
  ArrayData( "SPHEL", begin, end, nes, nssh ) {}

PhotoelectricCrossSectionBlock& operator=( const PhotoelectricCrossSectionBlock& ) = default;
PhotoelectricCrossSectionBlock& operator=( PhotoelectricCrossSectionBlock&& ) = default;
