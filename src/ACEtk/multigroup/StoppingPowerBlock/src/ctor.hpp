StoppingPowerBlock() = default;

StoppingPowerBlock( const StoppingPowerBlock& ) = default;
StoppingPowerBlock( StoppingPowerBlock&& ) = default;

StoppingPowerBlock& operator=( const StoppingPowerBlock& ) = default;
StoppingPowerBlock& operator=( StoppingPowerBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] stoppingPower      the stopping powers for each group
 */
StoppingPowerBlock( std::vector< double > stoppingPower ) :
  ArrayData( "STOP", std::vector< std::vector< double > >{ std::move( stoppingPower ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the STOP block in the XSS array
 *  @param[in] end     the end iterator of the STOP block in the XSS array
 *  @param[in] ngrp     the number of energy groups
 */
StoppingPowerBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
  ArrayData( "STOP", begin, end, ngrp, 1 ) {}
