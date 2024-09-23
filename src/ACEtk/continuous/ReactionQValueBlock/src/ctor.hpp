ReactionQValueBlock() = default;

ReactionQValueBlock( const ReactionQValueBlock& ) = default;
ReactionQValueBlock( ReactionQValueBlock&& ) = default;

ReactionQValueBlock& operator=( const ReactionQValueBlock& ) = default;
ReactionQValueBlock& operator=( ReactionQValueBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] qvalues    the Q values
 */
ReactionQValueBlock( std::vector< double > qvalues ) :
  ArrayData( "LQR",
             std::vector< std::vector< double > >{ std::move( qvalues ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the LQR block in the XSS array
 *  @param[in] end     the end iterator of the LQR block in the XSS array
 *  @param[in] ntr     the number of reactions (excluding elastic)
 */
ReactionQValueBlock( Iterator begin, Iterator end, unsigned int ntr ) :
  ArrayData( "LQR", begin, end, ntr, 1 ) {}
