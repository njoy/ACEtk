InelasticScatteringCrossSectionBlock() = default;

InelasticScatteringCrossSectionBlock( const InelasticScatteringCrossSectionBlock& ) = default;
InelasticScatteringCrossSectionBlock( InelasticScatteringCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies    the inelastic energies
 *  @param[in] xs          the inelastic cross section values
 */
InelasticScatteringCrossSectionBlock( std::vector< double > energies,
                                      std::vector< double > xs ) :
  ColumnData( "ITIE", std::move( energies ), std::move( xs ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the inelastic cross section block
 *  @param[in] end      the end iterator of the inelastic cross section block
 */
InelasticScatteringCrossSectionBlock( Iterator begin, Iterator end ) :
  ColumnData( "ITIE", begin, end, 2 ) {}

InelasticScatteringCrossSectionBlock& operator=( const InelasticScatteringCrossSectionBlock& ) = default;
InelasticScatteringCrossSectionBlock& operator=( InelasticScatteringCrossSectionBlock&& ) = default;
