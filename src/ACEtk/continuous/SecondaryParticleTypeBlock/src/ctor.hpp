SecondaryParticleTypeBlock() = default;

SecondaryParticleTypeBlock( const SecondaryParticleTypeBlock& ) = default;
SecondaryParticleTypeBlock( SecondaryParticleTypeBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] types    the secondary particle types
 */
SecondaryParticleTypeBlock( std::vector< unsigned int > types ) :
  ArrayData( "PTYPE",
             std::vector< std::vector< unsigned int > >{ std::move( types ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the PTYPE block in the XSS array
 *  @param[in] end     the end iterator of the PTYPE block in the XSS array
 *  @param[in] ntype   the number of secondary particle types
 */
SecondaryParticleTypeBlock( Iterator begin, Iterator end, unsigned int ntype ) :
  ArrayData( "PTYPE", begin, end, ntype, 1 ) {}

SecondaryParticleTypeBlock& operator=( const SecondaryParticleTypeBlock& ) = default;
SecondaryParticleTypeBlock& operator=( SecondaryParticleTypeBlock&& ) = default;
