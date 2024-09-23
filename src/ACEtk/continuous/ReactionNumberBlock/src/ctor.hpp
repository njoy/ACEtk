ReactionNumberBlock() = default;

ReactionNumberBlock( const ReactionNumberBlock& ) = default;
ReactionNumberBlock( ReactionNumberBlock&& ) = default;

ReactionNumberBlock& operator=( const ReactionNumberBlock& ) = default;
ReactionNumberBlock& operator=( ReactionNumberBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] mts    the MT numbers
 */
ReactionNumberBlock( std::vector< unsigned int > reactions ) :
  ArrayData( "MTR",
             std::vector< std::vector< unsigned int > >{ std::move( reactions ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the MTR block in the XSS array
 *  @param[in] end     the end iterator of the MTR block in the XSS array
 *  @param[in] ntr     the number of reactions (excluding elastic)
 */
ReactionNumberBlock( Iterator begin, Iterator end, unsigned int ntr ) :
  ArrayData( "MTR", begin, end, ntr, 1 ) {}
