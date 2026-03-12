EditReactionNumberBlock() = default;

EditReactionNumberBlock( const EditReactionNumberBlock& ) = default;
EditReactionNumberBlock( EditReactionNumberBlock&& ) = default;

EditReactionNumberBlock& operator=( const EditReactionNumberBlock& ) = default;
EditReactionNumberBlock& operator=( EditReactionNumberBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] editReactionNumbers    the edit reaction MT numbers
 */
EditReactionNumberBlock( std::vector< unsigned int > editReactionNumbers ) :
  ArrayData( "MTED", std::vector< std::vector< unsigned int > >{ std::move( editReactionNumbers ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the MTED block in the XSS array
 *  @param[in] end     the end iterator of the MTED block in the XSS array
 *  @param[in] nedit     the number of energy groups
 */
EditReactionNumberBlock( Iterator begin, Iterator end, unsigned int nedit ) :
  ArrayData( "MTED", begin, end, nedit, 1 ) {}
