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
std::cout << index << ' ' << start << ' ' << end << std::endl;
  return std::make_pair(
             begin + start - 1,
             end != 0 ? begin + end - 1
                      : start != 0 ? this->data().XSS().end()
                                   : begin + end - 1 );
}

void generateBlocks() {

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
  iterators = block( 4 );
  bool present = ( this->NFLO() > 0 );
  this->jflo_ = block::JFLO( present ? iterators.first : begin,
                             present ? iterators.second : begin,
                             this->NFLO() );

  // heating numbers
  iterators = block( 5 );
  this->lhnm_ = block::LHNM( iterators.first, iterators.second, this->NES() );

  // electron shell block
  auto locators = block( 6 );
  iterators = block( 8 );
  present = ( this->NSH() > 0 );
  this->eps_ = block::EPS( present ? locators.first : begin,
                           present ? iterators.second : begin,
                           this->NSH() );

  // compton profile block
  locators = block( 9 );
  iterators = block( 10 );
  present = ( this->NSH() > 0 );
  this->swd_ = block::SWD( present ? locators.first : begin,
                           present ? iterators.first : begin,
                           present ? iterators.second : begin,
                           this->NSH() );
}