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

auto block( std::size_t particle, std::size_t index ) const {

  // assumption: blocks are stored in sequence!

  auto begin = this->data().XSS().begin();
  std::size_t start = this->IXS()->LLOC( particle, index );

  // look for the first value that is larger than or equal to the start locator
  std::size_t end = 0;
  auto iter = std::find_if( this->IXS()->begin() + ( particle - 1 ) * 12 + index,
                            this->IXS()->end(),
                            [start] ( auto&& value ) { return value >= start; } );
  if ( iter != this->IXS()->end() ) {

    end = *iter;
  }

  return std::make_pair(
             begin + start - 1,
             end != 0 ? begin + end - 1 : this->data().XSS().end() );
}

void generateBlocks() {

  // starting iterator into the XSS array
  auto begin = this->data().XSS().begin();

  // principal cross section block
  unsigned int size = 3;
  if ( this->data().JXS(4) != 0 ) {

    size += 1;
  }
  auto locators = block( 1 );
  auto iterators = block( 6 );
  this->eszu_ = photonuclear::ESZU( locators.first, iterators.first, this->NES(), size );

  // reaction number block
  iterators = block( 6 );
  this->mtr_ = block::MTR( iterators.first, iterators.second, this->NTR() );

  // Q value block
  iterators = block( 7 );
  this->lqr_ = block::LQR( iterators.first, iterators.second, this->NTR() );

  // cross section block
  locators = block( 8 );
  iterators = block( 9 );
  this->sig_ = block::SIG( locators.first, iterators.first, iterators.second,
                           this->NTR() );

  // secondary particles
  bool present = ( this->NTYPE() > 0 );
  if ( present ) {

    // secondary particle information and locator block
    iterators = block( 10 );
    this->ixsu_ = photonuclear::IXSU( iterators.first, iterators.second, this->NTYPE() );

    // secondary particle data: data blocks
    for ( std::size_t index = 1; index <= this->NTYPE(); ++index ) {

      // secondary particle data: total production cross section
      iterators = block( index, 3 );
      this->pxs_.emplace_back( iterators.first, iterators.second );

      // secondary particle data: average heating cross section
      iterators = block( index, 4 );
      this->phn_.emplace_back( iterators.first, iterators.second );

      // secondary particle data: reaction numbers
      iterators = block( index, 5 );
      this->mtrh_.emplace_back( iterators.first, iterators.second,
                                this->IXS()->NP( index ) );

      // secondary particle data: reference frame and multiplicity
      iterators = block( index, 6 );
      this->tyrh_.emplace_back( iterators.first, iterators.second,
                                this->IXS()->NP( index ) );

      // secondary particle data: production cross section data
      locators = block( index, 7 );
      iterators = block( index, 8 );
      this->sigh_.emplace_back( locators.first, iterators.first, iterators.second,
                                this->IXS()->NP( index ) );

      // secondary particle data: angular distributions
      locators = block( index, 9 );
      iterators = block( index, 10 );
      this->andh_.emplace_back( locators.first, iterators.first, iterators.second,
                                this->IXS()->NP( index ) );

      // secondary particle data: energy distributions
      locators = block( index, 11 );
      iterators = block( index, 12 );
      this->dlwh_.emplace_back( locators.first, iterators.first, iterators.second,
                                this->TYRH( index ), this->IXS()->NP( index ) );
    }
  }
}
