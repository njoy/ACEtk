private:

/**
 *  @brief Private constructor
 */
SecondaryParticleInformationBlock( std::vector< unsigned int >&& numbers,
                                   std::size_t ntype ) :
  Base( "NTRO", generateXSS( std::move( numbers ) ) ),
  ntype_( ntype ) {}

public:

SecondaryParticleInformationBlock() = default;

SecondaryParticleInformationBlock( const SecondaryParticleInformationBlock& ) = default;
SecondaryParticleInformationBlock( SecondaryParticleInformationBlock&& ) = default;

SecondaryParticleInformationBlock& operator=( const SecondaryParticleInformationBlock& ) = default;
SecondaryParticleInformationBlock& operator=( SecondaryParticleInformationBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] numbers    the number of reactions for each secondary particle type
 */
SecondaryParticleInformationBlock( std::vector< unsigned int > numbers ) :
  SecondaryParticleInformationBlock( std::move( numbers ), numbers.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] ntro    the begin iterator of the NTRO block in the XSS array
 *  @param[in] end     the end iterator of the NTRO block in the XSS array
 *  @param[in] ntype   the number of secondary particle types
 */
SecondaryParticleInformationBlock( Iterator ntro, Iterator end, unsigned int ntype ) :
  Base( "NTRO", ntro, end ), ntype_( ntype ) {

  verifySize( this->begin(), this->end(), this->NTYPE() );
}
