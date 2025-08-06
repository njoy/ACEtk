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
  
  auto begin = this->data().XSS().begin();
  
  // transition energy block
  auto iterators = block( 1 );
  this->ekt_ = electron::EKT( iterators.first, iterators.second, this->NEL() );
  
  // radiation stopping power block
  auto iterators = block( 2 );
  this->rad_ = electron::RAD( iterators.first, iterators.second,
                              this->NRAD(), this->NEL() );
  
  // Mott scattering correction block
  auto iterators = block( 3 );
  this->mot_ = electron::MOT( iterators.first, iterators.second, this->NMOT() );
  
  // Riley cross section block
  auto iterators = block( 4 );
  this->rly_ = electron::RLY( iterators.first, iterators.second );
  
  if ( this->NEL() == 3 ) {
    
    // nullify unused blocks
    this->crb_ = std::nullopt;
    this->hfb_ = std::nullopt;
    
    // bremsstrahlung production block
    auto iterators = block( 5 );
    this->xsb_ = electron::XSB( iterators.first, iterators.second,
                                this->NEB(), this->NPB() );
    
    // bremsstrahlung energy spectrum block
    auto iterators = block( 9 );
    this->rkt_ = electron::RKT( iterators.first, iterators.second, this->NRKT() );
    
    // bremsstrahlung angular spectrum block
    auto iterators = block( 10 );
    this->rka_ = electron::RKA( iterators.first, iterators.second, this->NRKA() );
    
    // oscillator block
    auto iterators = block( 11 );
    this->osc_ = electron::OSC( iterators.first, iterators.second, this->NOSC() );
  } else {
    
    // nullify unused blocks
    this->xsb_ = std::nullopt;
    this->rkt_ = std::nullopt;
    this->rka_ = std::nullopt;
    this->osc_ = std::nullopt;
    
    // bremsstrahlung correction factor block
    auto iterators = block( 5 );
    this->crb_ = electron::CRB( iterators.first, iterators.second, this->NCRB() );
    
    // bremsstrahlung high frequency block
    auto iterators = block( 6 );
    this->hfb_ = electron::HFB( iterators.first, iterators.second, this->NHFB() );
  }
}
