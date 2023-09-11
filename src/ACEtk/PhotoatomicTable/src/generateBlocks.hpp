auto block( std::size_t index ) const {

  // assumption: blocks are stored in sequence!

  auto begin = this->data().XSS().begin();
  std::size_t start = this->data().JXS( index );

  std::size_t end = 0;
  if ( start != 0 ) {

    // look for the first value that is larger than or equal to the start locator
    auto iter = std::find_if( this->data().JXS().begin() + index,
                              this->data().JXS().end(),
                              [start] ( auto&& value ) { return value >= start; } );
    if ( iter != this->data().JXS().end() ) {

      end = *iter;
    }
  }

  return std::make_pair(
             begin + start - 1,
             end != 0 ? begin + end - 1
                      : start != 0 ? this->data().XSS().end()
                                   : begin + end - 1 );
}

void generateBlocks() {

  // optional blocks
  this->jflo_ = std::nullopt;
  this->eps_ = std::nullopt;
  this->swd_ = std::nullopt;
  this->subsh_ = std::nullopt;
  this->sphel_ = std::nullopt;
  this->esze_ = std::nullopt;
  this->excit_ = std::nullopt;

  // starting iterator into the XSS array
  auto begin = this->data().XSS().begin();

  // principal cross section data
  auto iterators = block( 1 );
  this->eszg_ = block::ESZG( iterators.first, iterators.second, this->NES() );

  // incoherent scattering functions
  iterators = block( 2 );
  this->jinc_ = block::JINC( iterators.first, iterators.second );

  // coherent form factor
  iterators = block( 3 );
  this->jcoh_ = block::JCOH( iterators.first, iterators.second );

  // fluorescence data block
  bool present = ( this->NFLO() > 0 );
  if ( present ) {

    iterators = block( 4 );
    this->jflo_ = block::JFLO( iterators.first, iterators.second, this->NFLO() );
  }

  // heating numbers
  iterators = block( 5 );
  this->lhnm_ = block::LHNM( iterators.first, iterators.second, this->NES() );

  present = ( this->NSH() > 0 );
  if ( present ) {

    // electron shell block
    auto locators = block( 6 );
    iterators = block( 8 );
    this->eps_ = block::EPS( locators.first, iterators.second, this->NSH() );

    // compton profile block
    locators = block( 9 );
    iterators = block( 10 );
    this->swd_ = block::SWD( locators.first, iterators.first, iterators.second,
                             this->NSH() );
  }

  present = ( this->NEPR() > 0 );
  if ( present ) {

    // electron subshell block and photolectric subshell cross section block
    auto subsh = block( 11 );
    auto sphel = block( 16 );
    this->subsh_ = block::SUBSH( subsh.first, sphel.first, this->NSSH() );
    this->sphel_ = block::SPHEL( sphel.first, sphel.second, this->NSSH(), this->NES() );

    auto esze = block( 19 );
    this->esze_ = block::ESZE( esze.first, esze.second, this->NSSH(), this->NE() );
    auto excit = block( 20 );
    this->excit_ = block::EXCIT( excit.first, excit.second, this->NXL() );

    auto breml = block( 26 );
    this->breml_ = block::BREML( breml.first, breml.second, this->NBL() );
  }
}
