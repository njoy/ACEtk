CrossSectionData() = default;

CrossSectionData( const CrossSectionData& ) = default;
CrossSectionData( CrossSectionData&& ) = default;

CrossSectionData& operator=( const CrossSectionData& ) = default;
CrossSectionData& operator=( CrossSectionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] xs              the xs values
 */
CrossSectionData( std::vector< long > boundaries,
                  std::vector< long > interpolants,
                  std::vector< double > energies,
                  std::vector< double > xs ) :
  TabulatedData( "CrossSectionData",
                 std::move( boundaries ), std::move( interpolants ),
                 std::move( energies ), std::move( xs ) ) {}

/**
 *  @brief Constructor (linear interpolation is assumed)
 *
 *  @param[in] energies        the energy values
 *  @param[in] xs              the xs values
 */
CrossSectionData( std::vector< double > energies,
                  std::vector< double > xs ) :
  CrossSectionData( {}, {}, std::move( energies ), std::move( xs ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
CrossSectionData( Iterator begin, Iterator end ) :
  TabulatedData( "CrossSectionData", begin, end ) {}
