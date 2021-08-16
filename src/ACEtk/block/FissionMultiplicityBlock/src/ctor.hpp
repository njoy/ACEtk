FissionMultiplicityBlock() = default;

FissionMultiplicityBlock( const FissionMultiplicityBlock& ) = default;
FissionMultiplicityBlock( FissionMultiplicityBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] prompt    the prompt fission multiplicity data
 */
FissionMultiplicityBlock( FissionMultiplicityData&& prompt ) :
  Base( "NU", generateXSS( std::move( prompt ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] prompt    the prompt fission multiplicity data
 *  @param[in] total     the total fission multiplicity data
 */
FissionMultiplicityBlock( FissionMultiplicityData&& prompt,
                          FissionMultiplicityData&& total ) :
  Base( "NU", generateXSS( std::move( prompt ), std::move( total ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the NU block in the XSS array
 *  @param[in] end      the end iterator of the NU block in the XSS array
 */
FissionMultiplicityBlock( Iterator begin, Iterator end ) :
  Base( "NU", begin, end ) {}

FissionMultiplicityBlock& operator=( const FissionMultiplicityBlock& ) = default;
FissionMultiplicityBlock& operator=( FissionMultiplicityBlock&& ) = default;
