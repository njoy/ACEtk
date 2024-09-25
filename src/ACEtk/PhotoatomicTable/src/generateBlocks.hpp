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

auto electroionisation_block( std::size_t index ) const {

  auto begin = this->data().XSS().begin();
  auto jxs23 = this->data().JXS( 23 );

  auto nssh = this->NSSH();
  auto n = *std::next( begin, jxs23 + index - 2 );
  auto start = std::next( begin, *std::next( begin, jxs23 + nssh + index - 2 ) - 1 );
  auto end = index != nssh
             ? std::next( begin, *std::next( begin, jxs23 + nssh + index - 1 ) - 1 )
             : std::next( begin, this->data().JXS( 24 ) - 1 );

  return std::make_tuple( start, end, n );
}

void generateBlocks() {

  // reset optional blocks
  this->jflo_ = std::nullopt;
  this->eps_ = std::nullopt;
  this->swd_ = std::nullopt;
  this->subsh_ = std::nullopt;
  this->sphel_ = std::nullopt;
  this->xprob_ = std::nullopt;
  this->esze_ = std::nullopt;
  this->excit_ = std::nullopt;
  this->elas_ = std::nullopt;
  this->breme_ = std::nullopt;
  this->breml_ = std::nullopt;
  this->selas_ = std::nullopt;

  // clear vectors
  eion_.clear();

  // starting iterator into the XSS array
  auto begin = this->data().XSS().begin();

  // principal cross section data
  auto iterators = block( 1 );
  this->eszg_ = photoatomic::ESZG( iterators.first, iterators.second, this->NES() );

  // incoherent scattering functions
  iterators = block( 2 );
  this->jinc_ = photoatomic::JINC( iterators.first, iterators.second );

  // coherent form factor
  iterators = block( 3 );
  this->jcoh_ = photoatomic::JCOH( iterators.first, iterators.second );

  // fluorescence data block
  bool present = ( this->NFLO() > 0 );
  if ( present ) {

    iterators = block( 4 );
    this->jflo_ = photoatomic::JFLO( iterators.first, iterators.second, this->NFLO() );
  }

  // heating numbers
  iterators = block( 5 );
  this->lhnm_ = photoatomic::LHNM( iterators.first, iterators.second, this->NES() );

  present = ( this->NSH() > 0 );
  if ( present ) {

    // electron shell block
    auto locators = block( 6 );
    iterators = block( 8 );
    this->eps_ = electron::EPS( locators.first, iterators.second, this->NSH() );

    // compton profile block
    locators = block( 9 );
    iterators = block( 10 );
    this->swd_ = photoatomic::SWD( locators.first, iterators.first, iterators.second,
                                   this->NSH() );
  }

  present = ( this->NEPR() > 0 );
  if ( present ) {

    auto subsh = block( 11 );
    auto sphel = block( 16 );
    this->subsh_ = electron::SUBSH( subsh.first, sphel.first, this->NSSH() );
    this->sphel_ = photoatomic::SPHEL( sphel.first, sphel.second, this->NSSH(), this->NES() );
    auto relo = block( 17 );
    auto xprob = block( 18 );
    this->xprob_ = electron::XPROB( relo.first, xprob.first, xprob.second, this->NSSH() );
    auto esze = block( 19 );
    this->esze_ = electron::ESZE( esze.first, esze.second, this->NSSH(), this->NE() );
    auto excit = block( 20 );
    this->excit_ = electron::EXCIT( excit.first, excit.second, this->NXL() );
    auto elasi = block( 21 );
    auto elas = block( 22 );
    this->elas_ = electron::ELAS( elasi.first, elas.second, this->NA() );

    // electronionisation
    for ( std::size_t index = 1; index <= this->NSSH(); ++index ) {

      auto eion = electroionisation_block( index );
      this->eion_.emplace_back( std::get< 0 >( eion ), std::get< 1 >( eion ),
                                std::get< 2 >( eion ) );
    }

    auto bremi = block( 24 );
    auto breme = block( 25 );
    this->breme_ = electron::BREME( bremi.first, breme.second, this->NB() );
    auto breml = block( 26 );
    this->breml_ = electron::BREML( breml.first, breml.second, this->NBL() );

    present = ( this->NEPR() == 3 );
    if ( present ) {

      auto selas = block( 27 );
      this->selas_ = electron::SELAS( selas.first, selas.second, this->NE() );
    }
  }
}
