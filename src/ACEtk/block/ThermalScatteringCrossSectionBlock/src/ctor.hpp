ThermalScatteringCrossSectionBlock() = default;

ThermalScatteringCrossSectionBlock( const ThermalScatteringCrossSectionBlock& ) = default;
ThermalScatteringCrossSectionBlock( ThermalScatteringCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies    the energies
 *  @param[in] xs          the cross section values
 */
ThermalScatteringCrossSectionBlock( std::vector< double > energies,
                                      std::vector< double > xs ) :
  ColumnData( "ThermalScatteringCrossSectionBlock",
              std::move( energies ), std::move( xs ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the thermal scattering cross section block
 *  @param[in] end      the end iterator of the thermal scattering cross section block
 */
ThermalScatteringCrossSectionBlock( Iterator begin, Iterator end ) :
  ColumnData( "ThermalScatteringCrossSectionBlock", begin, end, 2 ) {}

ThermalScatteringCrossSectionBlock& operator=( const ThermalScatteringCrossSectionBlock& ) = default;
ThermalScatteringCrossSectionBlock& operator=( ThermalScatteringCrossSectionBlock&& ) = default;
