private:

/**
 *  @brief Private constructor
 */
ReactionNumberBlock( std::vector< unsigned int >&& reactions, std::size_t ntr ) :
  Base( "MTR", generateXSS( std::move( reactions ) ) ),
  ntr_( ntr ) {}

public:

ReactionNumberBlock() = default;

ReactionNumberBlock( const ReactionNumberBlock& ) = default;
ReactionNumberBlock( ReactionNumberBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] mts    the MT numbers
 */
ReactionNumberBlock( std::vector< unsigned int >&& reactions ) :
  ReactionNumberBlock( std::move( reactions ), reactions.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] mtr   the begin iterator of the MTR block in the XSS array
 *  @param[in] end   the end iterator of the MTR block in the XSS array
 *  @param[in] ntr   the number of reactions (excluding elastic)
 */
ReactionNumberBlock( Iterator mtr, Iterator end, unsigned int ntr ) :
  Base( "MTR", mtr, end ), ntr_( ntr ) {

  verifySize( this->begin(), this->end(), this->ntr_ );
}

ReactionNumberBlock& operator=( const ReactionNumberBlock& ) = default;
ReactionNumberBlock& operator=( ReactionNumberBlock&& ) = default;
