FissionCrossSectionBlock() = default;

FissionCrossSectionBlock( const FissionCrossSectionBlock& ) = default;
FissionCrossSectionBlock( FissionCrossSectionBlock&& ) = default;

FissionCrossSectionBlock& operator=( const FissionCrossSectionBlock& ) = default;
FissionCrossSectionBlock& operator=( FissionCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] fissionCrossSection      the fission cross section for each group
 */
FissionCrossSectionBlock( std::vector< double > fissionCrossSection ) :
  ArrayData( "FISS", std::vector< std::vector< double > >{ std::move( fissionCrossSection ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the FISS block in the XSS array
 *  @param[in] end     the end iterator of the FISS block in the XSS array
 *  @param[in] ngrp     the number of energy groups
 */
FissionCrossSectionBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
  ArrayData( "FISS", begin, end, ngrp, 1 ) {}
