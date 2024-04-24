MultiplicityReactionNumberBlock() = default;

MultiplicityReactionNumberBlock( const MultiplicityReactionNumberBlock& ) = default;
MultiplicityReactionNumberBlock( MultiplicityReactionNumberBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] mts    the MT numbers
 */
MultiplicityReactionNumberBlock( std::vector< unsigned int > reactions ) :
  Base( "YP", generateXSS( std::move( reactions ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] yp    the begin iterator of the YP block in the XSS array
 *  @param[in] end   the end iterator of the YP block in the XSS array
 */
MultiplicityReactionNumberBlock( Iterator yp, Iterator end ) :
  Base( "YP", yp, end ) {

  verifySize( this->begin(), this->end(), this->NYP() );
}

MultiplicityReactionNumberBlock& operator=( const MultiplicityReactionNumberBlock& ) = default;
MultiplicityReactionNumberBlock& operator=( MultiplicityReactionNumberBlock&& ) = default;
