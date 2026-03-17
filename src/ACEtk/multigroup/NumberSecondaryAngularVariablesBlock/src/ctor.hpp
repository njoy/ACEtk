NumberSecondaryAngularVariablesBlock() = default;

NumberSecondaryAngularVariablesBlock( const NumberSecondaryAngularVariablesBlock& ) = default;
NumberSecondaryAngularVariablesBlock( NumberSecondaryAngularVariablesBlock&& ) = default;

NumberSecondaryAngularVariablesBlock& operator=( const NumberSecondaryAngularVariablesBlock& ) = default;
NumberSecondaryAngularVariablesBlock& operator=( NumberSecondaryAngularVariablesBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] numbers    the number of variables for each particle
 */
NumberSecondaryAngularVariablesBlock( std::vector< unsigned int > numbers ) :
  ArrayData( "NLEG2",
             std::vector< std::vector< unsigned int > >{ std::move( numbers ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the NLEG2 block in the XSS array
 *  @param[in] end     the end iterator of the NLEG2 block in the XSS array
 *  @param[in] nsec    the number of secondary particles
 */
NumberSecondaryAngularVariablesBlock( Iterator begin, Iterator end, unsigned int nsec ) :
  ArrayData( "NLEG2", begin, end, nsec, 1 ) {}
