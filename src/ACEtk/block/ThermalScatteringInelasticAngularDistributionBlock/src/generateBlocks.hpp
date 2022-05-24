void generateBlocks() {

  auto ne = this->NE();
  auto nc = this->NC();
  if ( this->IFENG() < 2 ) {

    auto nieb = this->NIEB().value();
    auto current = this->begin();
    auto end = current;
    for ( unsigned int incident = 1; incident <= ne; ++incident ) {

      std::vector< AngularDistributionData > data;
      for ( unsigned int outgoing = 1; outgoing <= nieb; ++outgoing ) {

        end = current + nc + 1;
        data.emplace_back( ThermalScatteringDiscreteCosines( nc, current, end ) );
        current = end;
      }
      this->data_.emplace_back( std::move( data ) );
    }
  }
  else {

    auto locator = this->relativeDistributionLocator( 1 );
    auto current = this->iterator( locator );
    auto end = current;
    for ( unsigned int incident = 1; incident <= ne; ++incident ) {

      locator = this->relativeDistributionLocator( incident + 1 );
      auto nieb = this->N( incident );
      auto next = incident == ne ? this->end() : this->iterator( locator );

      std::vector< AngularDistributionData > data;
      for ( unsigned int outgoing = 1; outgoing <= nieb; ++outgoing ) {

        end = outgoing == nieb ? next : current + nc + 3;
        if ( next < end ) {

          Log::error( "The size of the XSS array in the {} "
                      "block is smaller than expected", this->name() );
          Log::info( "XSS.size(): {}", this->length() );
          throw std::exception();
        }
        data.emplace_back( ThermalScatteringDiscreteCosinesWithProbability( nc, current, end ) );
        current = end;
      }
      this->data_.emplace_back( std::move( data ) );
    }
  }
}
