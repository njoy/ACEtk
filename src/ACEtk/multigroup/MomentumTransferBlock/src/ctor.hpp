MomentumTransferBlock() = default;

MomentumTransferBlock( const MomentumTransferBlock& ) = default;
MomentumTransferBlock( MomentumTransferBlock&& ) = default;

MomentumTransferBlock& operator=( const MomentumTransferBlock& ) = default;
MomentumTransferBlock& operator=( MomentumTransferBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] momentumTransfer      the momentum transfer for each group
 */
MomentumTransferBlock( std::vector< double > momentumTransfer ) :
  ArrayData( "MOM", std::vector< std::vector< double > >{ std::move( momentumTransfer ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the MOM block in the XSS array
 *  @param[in] end     the end iterator of the MOM block in the XSS array
 *  @param[in] ngrp     the number of energy groups
 */
MomentumTransferBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
  ArrayData( "MOM", begin, end, ngrp, 1 ) {}
