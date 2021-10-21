private:

/**
 *  @brief Private constructor
 */
SecondaryParticleTypeBlock( std::vector< unsigned int >&& types,
                            std::size_t ntype ) :
  Base( "PTYPE", generateXSS( std::move( types ) ) ),
  ntype_( ntype ) {}

public:

SecondaryParticleTypeBlock() = default;

SecondaryParticleTypeBlock( const SecondaryParticleTypeBlock& ) = default;
SecondaryParticleTypeBlock( SecondaryParticleTypeBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] types    the secondary particle types
 */
SecondaryParticleTypeBlock( std::vector< unsigned int >&& types ) :
  SecondaryParticleTypeBlock( std::move( types ), types.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] ptype   the begin iterator of the PTYPE block in the XSS array
 *  @param[in] end     the end iterator of the PTYPE block in the XSS array
 *  @param[in] ntype   the number of secondary particle types
 */
SecondaryParticleTypeBlock( Iterator ptype, Iterator end, unsigned int ntype ) :
  Base( "PTYPE", ptype, end ), ntype_( ntype ) {

  verifySize( this->begin(), this->end(), this->NTYPE() );
}

SecondaryParticleTypeBlock& operator=( const SecondaryParticleTypeBlock& ) = default;
SecondaryParticleTypeBlock& operator=( SecondaryParticleTypeBlock&& ) = default;