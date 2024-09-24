IncoherentScatteringFunctionBlock() = default;

IncoherentScatteringFunctionBlock( const IncoherentScatteringFunctionBlock& ) = default;
IncoherentScatteringFunctionBlock( IncoherentScatteringFunctionBlock&& ) = default;

IncoherentScatteringFunctionBlock& operator=( const IncoherentScatteringFunctionBlock& ) = default;
IncoherentScatteringFunctionBlock& operator=( IncoherentScatteringFunctionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] values    the scattering function values
 */
IncoherentScatteringFunctionBlock( std::vector< double > values ) :
  ArrayData( "JINC",
             generateArrays( std::move( values ) ) ) {

  momentum_ = {{ 0., .005, .01, .05, .1, .15, .2,
                 .3, .4, .5, .6, .7, .8, .9, 1., 1.5, 2., 3., 4., 5., 8. }};
}

/**
 *  @brief Constructor
 *
 *  @param[in] momentum    the momentum values
 *  @param[in] values      the scattering function values
 */
IncoherentScatteringFunctionBlock( std::vector< double > momentum,
                                   std::vector< double > values ) :
  ArrayData( "JINC", std::move( momentum ), std::move( values ) ) {}

private :

/**
 *  @brief Private intermediate constructor
 */
IncoherentScatteringFunctionBlock( Iterator begin, Iterator end,
                                   unsigned int size,
                                   unsigned int n, unsigned int m ) :
  ArrayData( "JINC", begin, end, n, m ), momentum_( std::nullopt ) {

  if ( size == 21 ) {

    momentum_ = {{ 0., .005, .01, .05, .1, .15, .2,
                   .3, .4, .5, .6, .7, .8, .9, 1., 1.5, 2., 3., 4., 5., 8. }};
  }
}

public:

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the JINC block in the XSS array
 *  @param[in] end     the end iterator of the JINC block in the XSS array
 */
IncoherentScatteringFunctionBlock( Iterator begin, Iterator end ) :
  IncoherentScatteringFunctionBlock( begin, end,
                                     std::distance( begin, end ),
                                     numberElements( begin, end ),
                                     numberArrays( begin, end ) ) {}
