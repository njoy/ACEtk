SubshellTransitionData() = default;

SubshellTransitionData( const SubshellTransitionData& ) = default;
SubshellTransitionData( SubshellTransitionData&& ) = default;

SubshellTransitionData& operator=( const SubshellTransitionData& ) = default;
SubshellTransitionData& operator=( SubshellTransitionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] primary          the primary subshell designators
 *  @param[in] secondary        the secondary subshell designators
 *  @param[in] energies         the energy values of the secondary photon or electron
 *  @param[in] probabilities    the cumulative probabilities of the transitions
 */
SubshellTransitionData(
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
SubshellTransitionData( Iterator begin, Iterator end ) :
  ArrayData( "TRAN", begin, end, 4, calculateNumberTransitions( begin, end ) ) {}
