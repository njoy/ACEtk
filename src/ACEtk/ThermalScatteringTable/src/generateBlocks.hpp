auto block( std::size_t index ) const {

  // assumption: blocks are stored in sequence!

  auto begin = this->data().XSS().begin();
  std::size_t start = this->data().JXS( index );

  std::size_t end = 0;
  if ( start != 0 ) {

    // look for the first value that is larger then or equal to the start locator
    auto iter = std::find_if( index == 1 || index == 4 || index == 7
                                ? this->data().JXS().begin() + index + 1
                                : this->data().JXS().begin() + index,
                              this->data().JXS().end(),
                              [start] ( auto&& value ) { return value >= start; } );
    if ( iter != this->data().JXS().end() ) {

      end = *iter;
    }
  }

  return std::make_pair(
             begin + start - 1,
             end != 0 ? begin + end - 1 : this->data().XSS().end() );
}

void generateBlocks() {

  // starting iterator into the XSS array
  auto begin = this->data().XSS().begin();

  // inelastic thermal scattering data
  bool present = this->data().JXS(1) > 0 ? true : false;
  auto iterators = block( 1 );
  this->itie_ = block::ITIE( present ? iterators.first : begin,
                             present ? iterators.second : begin );

  // coherent elastic thermal scattering data
  present = this->IDPNC() > 3 ? true : false;
  iterators = block( 4 );
  this->itce_ = block::ITCE( present ? iterators.first : begin,
                             present ? iterators.second : begin );

  // incoherent elastic thermal scattering data
  present = this->IDPNC() == 3 || this->IDPNC() == 5 ? true : false;
  iterators = this->IDPNC() == 3 ? block( 4 ) : block( 7 );
  this->itcei_ = block::ITCEI( present ? iterators.first : begin,
                               present ? iterators.second : begin );
}
