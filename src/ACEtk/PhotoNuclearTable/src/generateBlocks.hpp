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

// auto block( std::size_t particle, std::size_t index ) const {
//
//   // assumption: blocks are stored in sequence!
//
//   auto begin = this->data().XSS().begin();
//   std::size_t start = this->IXS().LLOC( particle, index );
//
//   // look for the first value that is larger than or equal to the start locator
//   std::size_t end = 0;
//   auto iter = std::find_if( this->IXS().begin() + ( particle - 1 ) * 10 + index,
//                             this->IXS().end(),
//                             [start] ( auto&& value ) { return value >= start; } );
//   if ( iter != this->IXS().end() ) {
//
//     end = *iter;
//   }
//
//   return std::make_pair(
//              begin + start - 1,
//              end != 0 ? begin + end - 1 : this->data().XSS().end() );
// }

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
  this->eszu_ = block::ESZU( locators.first, iterators.first, this->NES(), size );

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

  // secondary particle information and locator block
  iterators = block( 10 );
  bool present = ( this->NTYPE() > 0 );
  this->ixsu_ = block::IXSU( present ? iterators.first : begin,
                             present ? iterators.second : begin,
                             this->NTYPE() );
}
