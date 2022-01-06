auto block( std::size_t index ) const {

  // assumption: blocks are stored in sequence!

  auto begin = this->data().XSS().begin();
  std::size_t start = this->data().JXS( index );

  // look for the first value that is larger then or equal to the start locator
  auto iter = std::find_if( this->data().JXS().begin() + index,
                            this->data().JXS().end(),
                            [start] ( auto&& value ) { return value >= start; } );
  std::size_t end = 0;
  if ( iter != this->data().JXS().end() ) {

    // JXS(22) is not a locator, it points to the last value of the conventional
    // XSS array (i.e. before the secondary particle data)
    end = *iter != this->data().JXS(22) ? *iter : *iter + 1;
  }

  return std::make_pair(
             begin + start - 1,
             end != 0 ? begin + end - 1 : this->data().XSS().end() );
}

void generateBlocks() {

  // starting iterator into the XSS array
  auto begin = this->data().XSS().begin();

  // principal cross section block
  auto iterators = block( 1 );
  this->esz_ = block::ESZ( iterators.first, iterators.second, this->NES() );

  // nubar for fissile isotopes
  iterators = block( 2 );
  bool present = ( this->data().JXS(2) > 0 );
  this->nu_ = block::NU( present ? iterators.first : begin,
                         present ? iterators.second : begin );

  // reaction number block
  iterators = block( 3 );
  this->mtr_ = block::MTR( iterators.first, iterators.second, this->NTR() );

  // Q value block
  iterators = block( 4 );
  this->lqr_ = block::LQR( iterators.first, iterators.second, this->NTR() );

  // reference frame and multiplicity block
  iterators = block( 5 );
  this->tyr_ = block::TYR( iterators.first, iterators.second, this->NTR() );

  // cross section block
  auto locators = block( 6 );
  iterators = block( 7 );
  this->sig_ = block::SIG( locators.first, iterators.first, iterators.second,
                           this->NTR() );

  // angular distribution block
  locators = block( 8 );
  iterators = block( 9 );
  this->and_ = block::AND( locators.first, iterators.first, iterators.second,
                           this->NR() );

  // angular distribution block
  locators = block( 10 );
  iterators = block( 11 );
  this->dlw_ = block::DLW( locators.first, iterators.first, iterators.second,
                           this->NR() );

  // secondary photon data: total photon production cross section
  present = ( this->NTRP() > 0 );
  iterators = block( 12 );
  this->gpd_ = block::GPD( present ? iterators.first : begin,
                           present ? iterators.second : begin,
                           present ? this->NES() : 0 );

  // secondary photon data: photon production reaction numbers
  iterators = block( 13 );
  this->mtrp_ = block::MTR( present ? iterators.first : begin,
                            present ? iterators.second : begin,
                            this->NTRP() );

  // secondary photon data: photon production cross sections
  locators = block( 14 );
  iterators = block( 15 );
  this->sigp_ = block::SIGP( present ? locators.first : begin,
                             present ? iterators.first : begin,
                             present ? iterators.second : begin,
                             this->NTRP() );

  // secondary photon data: photon angular distributions
  locators = block( 16 );
  iterators = block( 17 );
  this->andp_ = block::ANDH( present ? locators.first : begin,
                             present ? iterators.first : begin,
                             present ? iterators.second : begin,
                             this->NTRP() );

  // secondary photon data: photon energy distributions
  locators = block( 18 );
  iterators = block( 19 );
  this->dlwp_ = block::DLW( present ? locators.first : begin,
                            present ? iterators.first : begin,
                            present ? iterators.second : begin,
                            this->NTRP() );

  // secondary photon data: photon yield data
  iterators = block( 20 );
  this->yp_ = block::YP( present ? iterators.first : begin,
                         present ? iterators.second : begin );

  // delayed neutron data: delayed nubar for fissile isotopes
  iterators = block( 24 );
  present = ( this->data().JXS(24) > 0 );
  this->dnu_ = block::NU( present ? iterators.first : begin,
                          present ? iterators.second : begin );

  // delayed neutron data: precursor data
  iterators = block( 25 );
  present = ( this->NPCR() > 0 );
  this->bdd_ = block::BDD( present ? iterators.first : begin,
                           present ? iterators.second : begin,
                           this->NPCR() );

  // secondary photon data: photon energy distributions
  locators = block( 26 );
  iterators = block( 27 );
  this->dned_ = block::DLW( present ? locators.first : begin,
                            present ? iterators.first : begin,
                            present ? iterators.second : begin,
                            this->NPCR() );

  // secondary particle data: available particle types
  iterators = block( 30 );
  present = ( this->NTYPE() > 0 );
  this->ptype_ = block::PTYPE( present ? iterators.first : begin,
                               present ? iterators.second : begin,
                               this->NTYPE() );
}
