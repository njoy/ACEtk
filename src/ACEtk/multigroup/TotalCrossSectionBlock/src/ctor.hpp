TotalCrossSectionBlock() = default;

TotalCrossSectionBlock( const TotalCrossSectionBlock& ) = default;
TotalCrossSectionBlock( TotalCrossSectionBlock&& ) = default;

TotalCrossSectionBlock& operator=( const TotalCrossSectionBlock& ) = default;
TotalCrossSectionBlock& operator=( TotalCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] totalCrossSection      the total cross section for each group
 */
TotalCrossSectionBlock( std::vector< double > totalCrossSection ) :
  ArrayData( "TOT", std::vector< std::vector< double > >{ std::move( totalCrossSection ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the TOT block in the XSS array
 *  @param[in] end     the end iterator of the TOT block in the XSS array
 *  @param[in] ngrp     the number of energy groups
 */
TotalCrossSectionBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
  ArrayData( "TOT", begin, end, ngrp, 1 ) {}
