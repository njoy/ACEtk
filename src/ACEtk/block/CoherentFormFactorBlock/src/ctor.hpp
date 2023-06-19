CoherentFormFactorBlock() = default;

CoherentFormFactorBlock( const CoherentFormFactorBlock& ) = default;
CoherentFormFactorBlock( CoherentFormFactorBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] integrated    the integrated form factor values
 *  @param[in] factors       the form factor values
 */
CoherentFormFactorBlock( std::vector< double > integrated,
                         std::vector< double > factors ) :
  ArrayData( "JCOH",
             std::vector< std::vector< double > >{ std::move( integrated ),
                                                   std::move( factors ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the JINC block in the XSS array
 *  @param[in] end     the end iterator of the JINC block in the XSS array
 */
CoherentFormFactorBlock( Iterator begin, Iterator end ) :
  ArrayData( "JCOH", begin, end, 55, 2 ) {}

CoherentFormFactorBlock& operator=( const CoherentFormFactorBlock& ) = default;
CoherentFormFactorBlock& operator=( CoherentFormFactorBlock&& ) = default;
