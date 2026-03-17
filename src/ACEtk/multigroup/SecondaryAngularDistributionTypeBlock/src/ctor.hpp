SecondaryAngularDistributionTypeBlock() = default;

SecondaryAngularDistributionTypeBlock( const SecondaryAngularDistributionTypeBlock& ) = default;
SecondaryAngularDistributionTypeBlock( SecondaryAngularDistributionTypeBlock&& ) = default;

SecondaryAngularDistributionTypeBlock& operator=( const SecondaryAngularDistributionTypeBlock& ) = default;
SecondaryAngularDistributionTypeBlock& operator=( SecondaryAngularDistributionTypeBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] types    the secondary angular distribution types
 */
SecondaryAngularDistributionTypeBlock( std::vector< unsigned int > types ) :
  ArrayData( "SANG2",
             std::vector< std::vector< unsigned int > >{ std::move( types ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the SANG2 block in the XSS array
 *  @param[in] end     the end iterator of the SANG2 block in the XSS array
 *  @param[in] nsec   the number of secondary particle types
 */
SecondaryAngularDistributionTypeBlock( Iterator begin, Iterator end, unsigned int nsec ) :
  ArrayData( "SANG2", begin, end, nsec, 1 ) {}
