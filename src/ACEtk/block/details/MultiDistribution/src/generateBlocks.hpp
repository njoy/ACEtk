void generateBlocks() {

  std::size_t locator = 1; // this->locb_ - ( this->locb_ - 1 )
  std::size_t lnw = 0;
  do {

    // lnw, law and idat from xss array (one based index starting at locb)
    lnw = static_cast< std::size_t >( this->IXSS( locator ) );
    EnergyDistributionType law =
        static_cast< EnergyDistributionType >( this->IXSS( locator + 1 ) );
    std::size_t idat = static_cast< std::size_t >( this->IXSS( locator + 2 ) );

    // iterators into the xss array (zero based index into internal xss array)
    auto pbegin = this->begin() + locator + 3 - 1;
    auto dbegin = this->begin() + idat - ( this->locb_ - 1 ) - 1;
    auto end = lnw ? this->begin() + lnw - ( this->locb_ - 1 ) - 1 : this->end();

    // add the probabilities to the xss array
    this->probabilities_.emplace_back( pbegin, dbegin );
    double emin = this->probabilities_.back().energies().front();
    double emax = this->probabilities_.back().energies().back();

    // add the actual distribution
    this->distributions_.emplace_back( Derived::readDistributionData(
                                                    law, dbegin, end,
                                                    emin, emax ) );

    // set the locator to the next law
    locator = lnw - ( this->locb_ - 1 );
  }
  while ( lnw != 0 );
}
