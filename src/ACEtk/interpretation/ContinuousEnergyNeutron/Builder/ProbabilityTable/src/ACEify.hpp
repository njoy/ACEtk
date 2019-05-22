  void ACEify( Table::Data& tData){
    decltype( auto ) xss = tData.XSS();

    xss |= ranges::action::push_back( this->CDFs );
    xss |= ranges::action::push_back( this->totalCrossSections );
    xss |= ranges::action::push_back( this->elasticCrossSections );
    xss |= ranges::action::push_back( this->fissionCrossSections );
    xss |= ranges::action::push_back( this->captureCrossSections );
    xss |= ranges::action::push_back( this->heating );
  }
