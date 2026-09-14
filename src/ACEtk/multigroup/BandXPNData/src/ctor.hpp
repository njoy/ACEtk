BandXPNData() = default;

BandXPNData( const BandXPNData& ) = default;
BandXPNData( BandXPNData&& ) = default;

BandXPNData& operator=( const BandXPNData& ) = default;
BandXPNData& operator=( BandXPNData&& ) = default;


/**
 *  @brief Constructor
*
*  Note: Any non-zero values in the matrix outside of the defined
*  bands will be lost in the construction of the BandXPNData 
*  object. 
 *
*  @param[in] matrix     the two-dimensional locator matrix
*  @param[in] down       the number of down-scatter groups
*  @param[in] up         the number of up-scatter groups
*/
BandXPNData( std::vector< std::vector< int > >&& matrix,
            unsigned int down, unsigned int up ) :
  SquareBandMatrixData( "BandXPNData", std::move( matrix ), down, up ) {}

/**
*  @brief Constructor
*
*  @param[in] begin      the begin iterator of the XPN data in the XSS array
*  @param[in] end        the end iterator of the XPN data in the XSS array
*  @param[in] ngrp       the number of energy groups
*  @param[in] down       the number of down-scatter groups
*  @param[in] up         the number of up-scatter groups
*/
BandXPNData( Iterator begin,
            Iterator end,
            unsigned int ngrp,
            unsigned int down,
            unsigned int up ) :
SquareBandMatrixData( "BandXPNData", begin, end, ngrp, down, up ) {}

