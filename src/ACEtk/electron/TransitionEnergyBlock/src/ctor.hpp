TransitionEnergyBlock() = default;

TransitionEnergyBlock( const TransitionEnergyBlock& ) = default;
TransitionEnergyBlock( TransitionEnergyBlock&& ) = default;

TransitionEnergyBlock& operator=( const TransitionEnergyBlock& ) = default;
TransitionEnergyBlock& operator=( TransitionEnergyBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] values    the various transition energy values
 */
TransitionEnergyBlock( std::vector< double > values ) :
  ArrayData( "EKT",
             std::vector< std::vector< double > >{ std::move( values ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the EKT block in the XSS array
 *  @param[in] end     the end iterator of the EKT block in the XSS array
 *  @param[in] nel     the el data format flag (0 or 3)
 */
TransitionEnergyBlock( Iterator begin, Iterator end, unsigned int nel ) :
  ArrayData( "EKT", begin, end, (nel == 3) ? 2 : 4, 1 ) {}
