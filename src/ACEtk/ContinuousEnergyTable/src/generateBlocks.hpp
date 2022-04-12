auto block( std::size_t index ) const {

  // assumption: blocks are stored in sequence!

  auto begin = this->data().XSS().begin();
  std::size_t start = this->data().JXS( index );

  std::size_t end = 0;
  if ( index != 32 ) {

    if ( start != 0 ) {

      // look for the first value that is larger then or equal to the start locator
      auto iter = std::find_if( this->data().JXS().begin() + index,
                                this->data().JXS().end(),
                                [start] ( auto&& value ) { return value >= start; } );
      if ( iter != this->data().JXS().end() ) {

        // JXS(22) is not a locator, it points to the last value of the conventional
        // XSS array (i.e. before the secondary particle data)
        end = *iter != this->data().JXS(22) ? *iter : *iter + 1;
      }

      // verify if out of order blocks exist (delayed neutron data before photons)
      switch ( index ) {

        // DLW ends either at GPD or UNR
        case 11 : {

          auto unr = this->data().JXS( 23 );
          if ( unr != 0 ) {

            if ( end > unr ) {

              end = unr;
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
  std::size_t start = this->IXS().LLOC( particle, index );

  // look for the first value that is larger then or equal to the start locator
  std::size_t end = 0;
  auto iter = std::find_if( this->IXS().begin() + ( particle - 1 ) * 10 + index,
                            this->IXS().end(),
                            [start] ( auto&& value ) { return value >= start; } );
  if ( iter != this->IXS().end() ) {

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

  // energy distribution block
  locators = block( 10 );
  iterators = block( 11 );
  this->dlw_ = block::DLW( locators.first, iterators.first, iterators.second,
                           this->TYR(), this->NR() );

  // secondary photon data: total photon production cross section
  present = ( this->NTRP() > 0 );
  iterators = block( 12 );
  this->gpd_ = block::GPD( present ? iterators.first : begin,
                           present ? iterators.second : begin,
                           present ? this->NES() : 0 );

  // secondary photon data: photon production reaction numbers
  iterators = block( 13 );
  this->mtrp_ = block::MTRP( present ? iterators.first : begin,
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
  this->andp_ = block::ANDP( present ? locators.first : begin,
                             present ? iterators.first : begin,
                             present ? iterators.second : begin,
                             this->NTRP() );

  // secondary photon data: photon energy distributions
  locators = block( 18 );
  iterators = block( 19 );
  this->dlwp_ = block::DLWP( present ? locators.first : begin,
                             present ? iterators.first : begin,
                             present ? iterators.second : begin,
                             this->NTRP() );

  // secondary photon data: photon yield data
  iterators = block( 20 );
  this->yp_ = block::YP( present ? iterators.first : begin,
                         present ? iterators.second : begin );

  // delayed neutron data: delayed nubar for fissile isotopes
  iterators = block( 23 );
  present = ( this->data().JXS(23) > 0 );
  this->unr_ = block::UNR( present ? iterators.first : begin,
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
  this->dned_ = block::DNED( present ? locators.first : begin,
                             present ? iterators.first : begin,
                             present ? iterators.second : begin,
                             this->NPCR() );

  // secondary particle data: available particle types
  iterators = block( 30 );
  present = ( this->NTYPE() > 0 );
  this->ptype_ = block::PTYPE( present ? iterators.first : begin,
                               present ? iterators.second : begin,
                               this->NTYPE() );

  // secondary particle data: number of reactions per type
  iterators = block( 31 );
  present = ( this->NTYPE() > 0 );
  this->ntro_ = block::NTRO( present ? iterators.first : begin,
                             present ? iterators.second : begin,
                             this->NTYPE() );

  // secondary particle data: number of reactions per type
  iterators = block( 32 );
  present = ( this->NTYPE() > 0 );
  this->ixs_ = block::IXS( present ? iterators.first : begin,
                           present ? iterators.second : begin,
                           this->NTYPE() );

  // secondary particle data: data blocks
  for ( std::size_t index = 1; index <= this->NTYPE(); ++index ) {

    // secondary particle data: total production cross section
    iterators = block( index, 1 );
    this->hpd_.emplace_back( iterators.first, iterators.second );

    // secondary particle data: reaction numbers
    iterators = block( index, 2 );
    this->mtrh_.emplace_back( iterators.first, iterators.second,
                              this->NTRO().NP( index ) );

    // secondary particle data: reference frame and multiplicity
    iterators = block( index, 3 );
    this->tyrh_.emplace_back( iterators.first, iterators.second,
                              this->NTRO().NP( index ) );

    // secondary particle data: production cross section data
    locators = block( index, 4 );
    iterators = block( index, 5 );
    this->sigh_.emplace_back( locators.first, iterators.first, iterators.second,
                              this->NTRO().NP( index ) );

    // secondary particle data: angular distributions
    locators = block( index, 6 );
    iterators = block( index, 7 );
    this->andh_.emplace_back( locators.first, iterators.first, iterators.second,
                              this->NTRO().NP( index ) );

    // secondary particle data: energy distributions
    locators = block( index, 8 );
    iterators = block( index, 9 );
    this->dlwh_.emplace_back( locators.first, iterators.first, iterators.second,
                              this->NTRO().NP( index ) );

    // secondary particle data: multiplicity reaction numbers
    iterators = block( index, 10 );
    this->yh_.emplace_back( iterators.first, iterators.second );
  }
}
