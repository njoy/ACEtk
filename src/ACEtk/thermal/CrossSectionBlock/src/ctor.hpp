CrossSectionBlock() = default;

CrossSectionBlock( const CrossSectionBlock& ) = default;
CrossSectionBlock( CrossSectionBlock&& ) = default;

CrossSectionBlock& operator=( const CrossSectionBlock& ) = default;
CrossSectionBlock& operator=( CrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies    the energies
 *  @param[in] xs          the cross section values
 */
CrossSectionBlock( std::vector< double > energies, std::vector< double > xs ) :
  ColumnData( "CrossSectionBlock",
              std::move( energies ), std::move( xs ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the thermal scattering cross section block
 *  @param[in] end      the end iterator of the thermal scattering cross section block
 */
CrossSectionBlock( Iterator begin, Iterator end ) :
  ColumnData( "CrossSectionBlock", begin, end, 2 ) {}
