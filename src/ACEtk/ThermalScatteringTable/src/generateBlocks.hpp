auto block( std::size_t index ) const {

  // assumption: blocks are stored in sequence!

  auto begin = this->data().XSS().begin();
  std::size_t start = this->data().JXS( index );

  std::size_t end = 0;
  if ( start != 0 ) {

    // look for the first value that is larger than or equal to the start locator
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
             end != 0 ? begin + end - 1
                      : start != 0 ? this->data().XSS().end()
                                   : begin + end - 1 );
}

void generateBlocks() {

  // reset optional blocks
  this->itce_ = std::nullopt;
  this->itca_ = std::nullopt;
  this->itcei_ = std::nullopt;
  this->itcai_ = std::nullopt;

  // starting iterator into the XSS array
  auto begin = this->data().XSS().begin();

  // inelastic thermal scattering data
  bool present = this->data().JXS(1) > 0 ? true : false;
  auto iterators = block( 1 );
  this->itie_ = thermal::ITIE( present ? iterators.first : begin,
                               present ? iterators.second : begin );

  iterators = block( 3 );
  this->itxe_ = thermal::ITXE( present ? this->IFENG() : 0,
                               present ? this->IFENG() < 2 ? this->NIEB() : 0 : 0,
                               present ? this->IFENG() < 2 ? this->NIL() + 1
                                                           : this->NIL() - 1
                                       : 0,
                               present ? this->ITIE().NE() : 0,
                               present ? this->data().JXS(3) : 1,
                               present ? iterators.first : begin,
                               present ? iterators.second : begin );

  // coherent elastic thermal scattering data
  present = this->IDPNC() > 3 ? true : false;
  if ( present ) {

    iterators = block( 4 );
    this->itce_ = thermal::ITCE( iterators.first, iterators.second );

    present = this->NCL() + 1 != 0 ? true : false;
    if ( present ) {

      iterators = block( 6 );
      this->itca_ = thermal::ITCA( iterators.first, iterators.second,
                                   this->ITCE()->NE(), this->NCL() + 1 );
    }
  }

  // incoherent elastic thermal scattering data
  present = this->IDPNC() == 3 || this->IDPNC() == 5 ? true : false;
  if ( present ) {

    iterators = this->IDPNC() == 3 ? block( 4 ) : block( 7 );
    this->itcei_ = thermal::ITCEI( iterators.first, iterators.second );

    iterators = this->IDPNC() == 3 ? block( 6 ) : block( 9 );
    this->itcai_ = thermal::ITCA( iterators.first, iterators.second,
                                  this->ITCEI()->NE(),
                                  this->IDPNC() == 3 ? this->NCL() + 1
                                                     : this->NCLI() + 1 );
  }
}
