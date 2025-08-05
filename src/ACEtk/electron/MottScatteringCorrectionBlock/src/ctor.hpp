MottScatteringCorrectionBlock() = default;

MottScatteringCorrectionBlock( const MottScatteringCorrectionBlock& ) = default;
MottScatteringCorrectionBlock( MottScatteringCorrectionBlock&& ) = default;

MottScatteringCorrectionBlock& operator=( const MottScatteringCorrectionBlock& ) = default;
MottScatteringCorrectionBlock& operator=( MottScatteringCorrectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies             the energy values
 *  @param[in] corrections0deg      the Mott scattering corrections at 0 degrees
 *  @param[in] corrections45deg     the Mott scattering corrections at 45 degrees
 *  @param[in] corrections90deg     the Mott scattering corrections at 90 degrees
 *  @param[in] corrections135deg    the Mott scattering corrections at 135 degrees
 *  @param[in] corrections180deg    the Mott scattering corrections at 180 degrees
 */
MottScatteringCorrectionBlock( std::vector< double > energies,
                               std::vector< double > corrections0deg,
                               std::vector< double > corrections45deg,
                               std::vector< double > corrections90deg,
                               std::vector< double > corrections135deg,
                               std::vector< double > corrections180deg ) :
  ArrayData( "MOT",
             std::move( energies ), std::move( corrections0deg ),
             std::move( corrections45deg ), std::move( corrections90deg ),
             std::move( corrections135deg ), std::move( corrections180deg ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the ESZG block in the XSS array
 *  @param[in] end     the end iterator of the ESZG block in the XSS array
 *  @param[in] nmot    the number of energy points
 */
MottScatteringCorrectionBlock( Iterator begin, Iterator end, unsigned int nmot ) :
  ArrayData( "MOT", begin, end, nmot, 6 ) {}
