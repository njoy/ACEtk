private:

/**
 *  @brief Private constructor
 */
FrameAndMultiplicityBlock( std::vector< ReferenceFrame >&& frames,
                           std::vector< unsigned int >&& multiplicities,
                           std::size_t ntr ) :
  Base( "TYR", generateXSS( std::move( frames ), std::move( multiplicities ) ) ),
  ntr_( ntr ) {}

/**
 *  @brief Private constructor
 */
FrameAndMultiplicityBlock( std::vector< ReferenceFrame >&& frames,
                           std::size_t ntr ) :
  Base( "TYR", generateXSS( std::move( frames ) ) ), ntr_( ntr ) {}

public:

FrameAndMultiplicityBlock() = default;

FrameAndMultiplicityBlock( const FrameAndMultiplicityBlock& ) = default;
FrameAndMultiplicityBlock( FrameAndMultiplicityBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] frames            the reference frames
 *  @param[in] multiplicities    the multiplicities
 */
FrameAndMultiplicityBlock( std::vector< ReferenceFrame > frames,
                           std::vector< unsigned int > multiplicities ) :
  FrameAndMultiplicityBlock( std::move( frames ), std::move( multiplicities ),
                             frames.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] frames            the reference frames
 */
FrameAndMultiplicityBlock( std::vector< ReferenceFrame > frames ) :
  FrameAndMultiplicityBlock( std::move( frames ), frames.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] mtr   the begin iterator of the TYR block in the XSS array
 *  @param[in] end   the end iterator of the TYR block in the XSS array
 *  @param[in] ntr   the number of reactions (excluding elastic)
 */
FrameAndMultiplicityBlock( Iterator tyr, Iterator end, unsigned int ntr ) :
  Base( "TYR", tyr, end ), ntr_( ntr ) {

  verifySize( this->begin(), this->end(), this->ntr_ );
}

FrameAndMultiplicityBlock& operator=( const FrameAndMultiplicityBlock& ) = default;
FrameAndMultiplicityBlock& operator=( FrameAndMultiplicityBlock&& ) = default;
