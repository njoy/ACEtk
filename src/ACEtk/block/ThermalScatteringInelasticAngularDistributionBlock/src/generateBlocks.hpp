void generateBlocks() {

  if ( this->IFENG() < 2 ) {

    auto ne = this->NE();
    auto nieb = this->NIEB().value();
    auto nc = this->NC();
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


  }
}
