auto block( std::size_t index ) const {

  // assumption: blocks are stored in sequence!

  auto begin = this->data().XSS().begin();
  std::size_t start = this->data().JXS( index );

  std::size_t end = 0;
  if ( index != 32 ) {

    if ( start != 0 ) {

      // look for the first value that is larger than or equal to the start locator
      auto iter = std::find_if( this->data().JXS().begin() + index,
                                this->data().JXS().end(),
                                [start] ( auto&& value ) { return value >= start; } );
      if ( iter != this->data().JXS().end() ) {

        // JXS(22) is not a locator, it points to the last value of the conventional
        // XSS array (i.e. before the secondary particle data)
        end = *iter != this->data().JXS(22) ? *iter : *iter + 1;

        // JXS(21) does not point to an actual block so set it to END + 1 instead
        if ( end == this->data().JXS(21) ) {

          end = this->data().JXS(22) + 1;
        }
      }

      // verify if out of order blocks exist (delayed neutron data before photons)
      switch ( index ) {

        // DLW ends either at GPD or one of the blocks past JXS(22)
        case 11 : {

          iter = std::find_if( this->data().JXS().begin() + 22,
                               this->data().JXS().end(),
                               [start] ( auto&& value ) { return value >= start; } );

          if ( iter != this->data().JXS().end() ) {

            auto next = *iter;
            if ( end > next ) {

              end = next;
            }
          }
          break;
        }
        // DEND ends either at GPD or END
        case 27 : {

          if ( end == 0 ) {

            end = this->data().JXS(22) + 1;
          }

          auto gpd = this->data().JXS( 12 );
          if ( gpd != 0 ) {

            if ( end > gpd ) {

              end = gpd;
            }
          }
          break;
        }
        default: break;
      }
    }
  }
  else {

    if ( this->NTYPE() != 0 ) {

      end = start + this->NTYPE() * 10 + 1;
    }
  }

  return std::make_pair(
             begin + start - 1,
             end != 0 ? begin + end - 1 : this->data().XSS().end() );
}

auto block( std::size_t particle, std::size_t index ) const {

  // assumption: blocks are stored in sequence!

  auto begin = this->data().XSS().begin();
  std::size_t start = this->IXS()->LLOC( particle, index );

  // look for the first value that is larger then or equal to the start locator
  std::size_t end = 0;
  auto iter = std::find_if( this->IXS()->begin() + ( particle - 1 ) * 10 + index,
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

  // reset optional blocks
  this->nu_ = std::nullopt;
  this->gpd_ = std::nullopt;
  this->mtrp_ = std::nullopt;
  this->sigp_ = std::nullopt;
  this->andp_ = std::nullopt;
  this->dlwp_ = std::nullopt;
  this->yp_ = std::nullopt;
  this->unr_ = std::nullopt;
  this->dnu_ = std::nullopt;
  this->bdd_ = std::nullopt;
  this->dned_ = std::nullopt;
  this->ptype_ = std::nullopt;
  this->ntro_ = std::nullopt;
  this->ixs_ = std::nullopt;

  // clear vectors
  this->hpd_.clear();
  this->mtrh_.clear();
  this->tyrh_.clear();
  this->sigh_.clear();
  this->andh_.clear();
  this->dlwh_.clear();
  this->yh_.clear();

  // starting iterator into the XSS array
  auto begin = this->data().XSS().begin();

  // principal cross section block
  auto iterators = block( 1 );
  this->esz_ = continuous::ESZ( iterators.first, iterators.second, this->NES() );

  // nubar for fissile isotopes
  bool present = ( this->data().JXS(2) > 0 );
  if ( present ) {

    iterators = block( 2 );
    this->nu_ = continuous::NU( iterators.first, iterators.second );
  }

  // reaction number block
  iterators = block( 3 );
  this->mtr_ = continuous::MTR( iterators.first, iterators.second, this->NTR() );

  // Q value block
  iterators = block( 4 );
  this->lqr_ = continuous::LQR( iterators.first, iterators.second, this->NTR() );

  // reference frame and multiplicity block
  iterators = block( 5 );
  this->tyr_ = continuous::TYR( iterators.first, iterators.second, this->NTR() );

  // cross section block
  auto locators = block( 6 );
  iterators = block( 7 );
  this->sig_ = continuous::SIG( locators.first, iterators.first, iterators.second,
                                this->NTR() );

  // angular distribution block
  locators = block( 8 );
  iterators = block( 9 );
  this->and_ = continuous::AND( locators.first, iterators.first, iterators.second,
                                this->NR() );

  // energy distribution block
  locators = block( 10 );
  iterators = block( 11 );
  this->dlw_ = continuous::DLW( locators.first, iterators.first, iterators.second,
                                this->TYR(), this->NR() );

  // secondary photon data
  present = ( this->NTRP() > 0 );
  if ( present ) {

    // secondary photon data: total photon production cross section
    iterators = block( 12 );
    this->gpd_ = continuous::GPD( iterators.first, iterators.second, this->NES() );

    // secondary photon data: photon production reaction numbers
    iterators = block( 13 );
    this->mtrp_ = continuous::MTRP( iterators.first, iterators.second, this->NTRP() );

    // secondary photon data: photon production cross sections
    locators = block( 14 );
    iterators = block( 15 );
    this->sigp_ = continuous::SIGP( locators.first, iterators.first, iterators.second,
                                    this->NTRP() );

    // secondary photon data: photon angular distributions
    locators = block( 16 );
    iterators = block( 17 );
    this->andp_ = continuous::ANDP( locators.first, iterators.first, iterators.second,
                                    this->NTRP() );

    // secondary photon data: photon energy distributions
    locators = block( 18 );
    iterators = block( 19 );
    this->dlwp_ = continuous::DLWP( locators.first, iterators.first, iterators.second,
                                    this->NTRP() );

    // secondary photon data: photon yield data
    iterators = block( 20 );
    this->yp_ = continuous::YP( iterators.first, iterators.second );
  }

  // unresolved resonance tables
  present = ( this->data().JXS(23) > 0 );
  if ( present ) {

    iterators = block( 23 );
    this->unr_ = continuous::UNR( iterators.first, iterators.second );
  }

  // delayed neutron data: delayed nubar for fissile isotopes
  present = ( this->data().JXS(24) > 0 );
  if ( present ) {

    iterators = block( 24 );
    this->dnu_ = continuous::NU( iterators.first, iterators.second );
  }

  // delayed neutron data
  present = ( this->NPCR() > 0 );
  if ( present ) {

    // delayed neutron data: precursor data
    iterators = block( 25 );
    this->bdd_ = continuous::BDD( iterators.first, iterators.second, this->NPCR() );

    // delayed neutron data: spectra
    locators = block( 26 );
    iterators = block( 27 );
    this->dned_ = continuous::DNED( locators.first, iterators.first, iterators.second,
                                    this->NPCR() );
  }

  // secondary particle data
  present = ( this->NTYPE() > 0 );
  if ( present ) {

    // secondary particle data: available particle types
    iterators = block( 30 );
    this->ptype_ = continuous::PTYPE( iterators.first, iterators.second, this->NTYPE() );

    // secondary particle data: number of reactions per type
    iterators = block( 31 );
    this->ntro_ = continuous::NTRO( iterators.first, iterators.second, this->NTYPE() );

    // secondary particle data: number of reactions per type
    iterators = block( 32 );
    this->ixs_ = continuous::IXS( iterators.first, iterators.second, this->NTYPE() );

    // secondary particle data: data blocks
    for ( std::size_t index = 1; index <= this->NTYPE(); ++index ) {

      // secondary particle data: total production cross section
      iterators = block( index, 1 );
      this->hpd_.emplace_back( iterators.first, iterators.second );

      // secondary particle data: reaction numbers
      iterators = block( index, 2 );
      this->mtrh_.emplace_back( iterators.first, iterators.second,
                                this->NTRO()->NP( index ) );

      // secondary particle data: reference frame and multiplicity
      iterators = block( index, 3 );
      this->tyrh_.emplace_back( iterators.first, iterators.second,
                                this->NTRO()->NP( index ) );

      // secondary particle data: production cross section data
      locators = block( index, 4 );
      iterators = block( index, 5 );
      this->sigh_.emplace_back( locators.first, iterators.first, iterators.second,
                                this->NTRO()->NP( index ) );

      // secondary particle data: angular distributions
      locators = block( index, 6 );
      iterators = block( index, 7 );
      this->andh_.emplace_back( locators.first, iterators.first, iterators.second,
                                this->NTRO()->NP( index ) );

      // secondary particle data: energy distributions
      locators = block( index, 8 );
      iterators = block( index, 9 );
      this->dlwh_.emplace_back( locators.first, iterators.first, iterators.second,
                                this->TYRH( index ), this->NTRO()->NP( index ) );

      // secondary particle data: multiplicity reaction numbers
      iterators = block( index, 10 );
      this->yh_.emplace_back( iterators.first, iterators.second );
    }
  }
}
