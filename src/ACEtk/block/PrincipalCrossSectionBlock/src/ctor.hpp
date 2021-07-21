PrincipalCrossSectionBlock() = default;

PrincipalCrossSectionBlock( const PrincipalCrossSectionBlock& ) = default;
PrincipalCrossSectionBlock( PrincipalCrossSectionBlock&& ) = default;

PrincipalCrossSectionBlock( std::vector< double >&& energies,
                            std::vector< double >&& total,
                            std::vector< double >&& disappearance,
                            std::vector< double >&& elastic,
                            std::vector< double >&& heating ) :
  Base( generateXSS( std::move( energies ), std::move( total ),
                     std::move( disappearance ), std::move( elastic ),
                     std::move( heating ) ) ),
  nes_( energies.size() ) {}

PrincipalCrossSectionBlock( Iterator begin, Iterator end, unsigned int nes ) :
  Base( begin, end ), nes_( nes ) {

  verifySize( this->begin(), this->end(), this->nes_ );    
}

PrincipalCrossSectionBlock& operator=( const PrincipalCrossSectionBlock& ) = default;
PrincipalCrossSectionBlock& operator=( PrincipalCrossSectionBlock&& ) = default;
