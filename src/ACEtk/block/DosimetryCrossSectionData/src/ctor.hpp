DosimetryCrossSectionData() = default;

DosimetryCrossSectionData( const DosimetryCrossSectionData& ) = default;
DosimetryCrossSectionData( DosimetryCrossSectionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] xs              the xs values
 */
DosimetryCrossSectionData( std::vector< long >&& boundaries,
                           std::vector< long >&& interpolants,
                           std::vector< double >&& energies,
                           std::vector< double >&& xs ) :
  BaseTabulatedData( "SIGD::DosimetryCrossSectionData",
                     std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( xs ) ) {}

/**
 *  @brief Constructor (linear interpolation is assumed)
 *
 *  @param[in] energies        the energy values
 *  @param[in] xs              the xs values
 */
DosimetryCrossSectionData( std::vector< double >&& energies,
                           std::vector< double >&& xs ) :
  DosimetryCrossSectionData( {}, {}, std::move( energies ), std::move( xs ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
DosimetryCrossSectionData( Iterator begin, Iterator end ) :
  BaseTabulatedData( "SIGD::DosimetryCrossSectionData", begin, end ) {}

DosimetryCrossSectionData& operator=( const DosimetryCrossSectionData& ) = default;
DosimetryCrossSectionData& operator=( DosimetryCrossSectionData&& ) = default;
