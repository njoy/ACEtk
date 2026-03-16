BandP0Data() = default;

BandP0Data( const BandP0Data& ) = default;
BandP0Data( BandP0Data&& ) = default;

BandP0Data& operator=( const BandP0Data& ) = default;
BandP0Data& operator=( BandP0Data&& ) = default;


/**
 *  @brief Constructor
*
*  Note: Any non-zero values in the matrix outside of the defined
*  bands will be lost in the construction of the BandP0Data 
*  object. 
 *
*  @param[in] vals       the two-dimensional matrix data values
*  @param[in] down       the number of down-scatter groups
*  @param[in] up         the number of up-scatter groups
*/
BandP0Data( std::vector< std::vector< double > >&& vals,
            unsigned int down, unsigned int up ) :
  SquareBandMatrixData( "BandP0Data", std::move( vals ), down, up ) {}

/**
*  @brief Constructor
*
*  @param[in] begin      the begin iterator of the P0 data in the XSS array
*  @param[in] end        the end iterator of the P0 data in the XSS array
*  @param[in] ngrp       the number of energy groups
*  @param[in] down       the number of down-scatter groups
*  @param[in] up         the number of up-scatter groups
*/
BandP0Data( Iterator begin,
            Iterator end,
            unsigned int ngrp,
            unsigned int down,
            unsigned int up ) :
SquareBandMatrixData( "BandP0Data", begin, end, ngrp, down, up ) {}

