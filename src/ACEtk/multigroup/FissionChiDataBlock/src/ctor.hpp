FissionChiDataBlock() = default;

FissionChiDataBlock( const FissionChiDataBlock& ) = default;
FissionChiDataBlock( FissionChiDataBlock&& ) = default;

FissionChiDataBlock& operator=( const FissionChiDataBlock& ) = default;
FissionChiDataBlock& operator=( FissionChiDataBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] fissionFraction      the fission fraction (PFNS) for each group
 */
FissionChiDataBlock( std::vector< double > fissionFraction ) :
  ArrayData( "CHI", std::vector< std::vector< double > >{ std::move( fissionFraction ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the CHI block in the XSS array
 *  @param[in] end     the end iterator of the CHI block in the XSS array
 *  @param[in] ngrp     the number of energy groups
 */
FissionChiDataBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
  ArrayData( "CHI", begin, end, ngrp, 1 ) {}
