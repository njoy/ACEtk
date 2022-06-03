IncoherentScatteringFunctionBlock() = default;

IncoherentScatteringFunctionBlock( const IncoherentScatteringFunctionBlock& ) = default;
IncoherentScatteringFunctionBlock( IncoherentScatteringFunctionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] values    the scattering function values
 */
IncoherentScatteringFunctionBlock( std::vector< double > values ) :
  ArrayData( "JINC",
             std::vector< std::vector< double > >{ std::move( values ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the JINC block in the XSS array
 *  @param[in] end     the end iterator of the JINC block in the XSS array
 */
IncoherentScatteringFunctionBlock( Iterator begin, Iterator end ) :
  ArrayData( "JINC", begin, end, 21, 1 ) {}

IncoherentScatteringFunctionBlock& operator=( const IncoherentScatteringFunctionBlock& ) = default;
IncoherentScatteringFunctionBlock& operator=( IncoherentScatteringFunctionBlock&& ) = default;
