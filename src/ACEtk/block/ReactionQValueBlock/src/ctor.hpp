ReactionQValueBlock() = default;

ReactionQValueBlock( const ReactionQValueBlock& ) = default;
ReactionQValueBlock( ReactionQValueBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] qvalues    the Q values
 */
ReactionQValueBlock( std::vector< double >&& qvalues ) :
  Base( "LQR", std::move( qvalues ) ),
  ntr_( qvalues.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lqr   the begin iterator of the LQR block in the XSS array
 *  @param[in] end   the end iterator of the LQR block in the XSS array
 *  @param[in] ntr   the number of reactions (excluding elastic)
 */
ReactionQValueBlock( Iterator lqr, Iterator end, unsigned int ntr ) :
  Base( "LQR", lqr, end ), ntr_( ntr ) {

  verifySize( this->begin(), this->end(), this->ntr_ );
}

ReactionQValueBlock& operator=( const ReactionQValueBlock& ) = default;
ReactionQValueBlock& operator=( ReactionQValueBlock&& ) = default;
