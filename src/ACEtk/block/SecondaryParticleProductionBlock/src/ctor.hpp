SecondaryParticleProductionBlock() = default;

SecondaryParticleProductionBlock( const SecondaryParticleProductionBlock& ) = default;
SecondaryParticleProductionBlock( SecondaryParticleProductionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] index         the energy index
 *  @param[in] production    the total production cross section values
 *  @param[in] heating       the heating values
 */
SecondaryParticleProductionBlock( std::size_t index,
                                  std::vector< double > production,
                                  std::vector< double > heating ) :
  Base( "HPD", generateXSS( index, std::move( production ),
                            std::move( heating ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the cross section data
 *  @param[in] end      the end iterator of the cross section data
 */
SecondaryParticleProductionBlock( Iterator begin, Iterator end ) :
  Base( "HPD", begin, end ) {

  verifySize( this->begin(), this->end(), this->numberValues() );
}

SecondaryParticleProductionBlock& operator=( const SecondaryParticleProductionBlock& ) = default;
SecondaryParticleProductionBlock& operator=( SecondaryParticleProductionBlock&& ) = default;
