PhotoatomicSubshellTransitionData() = default;

PhotoatomicSubshellTransitionData( const PhotoatomicSubshellTransitionData& ) = default;
PhotoatomicSubshellTransitionData( PhotoatomicSubshellTransitionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies    the energy values
 *  @param[in] loss        the average excitation energy loss values
 */
PhotoatomicSubshellTransitionData(
    std::vector< unsigned int > primary,
    std::vector< unsigned int > secondary,
    std::vector< double > energies,
    std::vector< double > probabilities ) :
  ArrayData( "TRAN",
             generateArrays( std::move( primary ), std::move( secondary ),
                             std::move( energies ), std::move( probabilities ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the transition data in the XSS array
 *  @param[in] end     the end iterator of the transition data in the XSS array
 *  @param[in] nt      the number of transitions
 */
PhotoatomicSubshellTransitionData( Iterator begin, Iterator end ) :
  ArrayData( "TRAN", begin, end, 4, calculateNumberTransitions( begin, end ) ) {}

PhotoatomicSubshellTransitionData& operator=( const PhotoatomicSubshellTransitionData& ) = default;
PhotoatomicSubshellTransitionData& operator=( PhotoatomicSubshellTransitionData&& ) = default;
