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
             generateArrays( std::move( integrated ), std::move( factors ) ) ) {

  momentum_ = {{ 0., .01, .02, .03, .04, .05, .06, .08, .10, .12, .15,
                .18, .20, .25, .30, .35, .40, .45, .50, .55, .60, .70,
                .80, .90, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8,
                1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8,
                4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0 }};
}

/**
 *  @brief Constructor
 *
 *  @param[in] momentum      the momemtum values
 *  @param[in] integrated    the integrated form factor values
 *  @param[in] factors       the form factor values
 */
CoherentFormFactorBlock( std::vector< double > momentum,
                         std::vector< double > integrated,
                         std::vector< double > factors ) :
  ArrayData( "JCOH", std::move( momentum ), std::move( integrated ), 
                     std::move( factors ) ) {}

private :

/**
 *  @brief Private intermediate constructor
 */
CoherentFormFactorBlock( Iterator begin, Iterator end, 
                         unsigned int size, 
                         unsigned int n, unsigned int m ) :
  ArrayData( "JCOH", begin, end, n, m ), momentum_( std::nullopt ) {

  if ( size == 110 ) {

    momentum_ = {{ 0., .01, .02, .03, .04, .05, .06, .08, .10, .12, .15,
                  .18, .20, .25, .30, .35, .40, .45, .50, .55, .60, .70,
                  .80, .90, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8,
                  1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8,
                  4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0 }};
  }
}

public:

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the JINC block in the XSS array
 *  @param[in] end     the end iterator of the JINC block in the XSS array
 */
CoherentFormFactorBlock( Iterator begin, Iterator end ) :
  CoherentFormFactorBlock( begin, end, 
                           std::distance( begin, end ), 
                           numberElements( begin, end ), 
                           numberArrays( begin, end ) ) {}

CoherentFormFactorBlock& operator=( const CoherentFormFactorBlock& ) = default;
CoherentFormFactorBlock& operator=( CoherentFormFactorBlock&& ) = default;

