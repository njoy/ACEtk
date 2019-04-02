void ACEify( Table::Data& tData, int ){
  tData.XSS()
    |= ranges::action::push_back(
      ranges::view::concat(
        ranges::view::single( this->interpolationParameter ),
        ranges::view::single( this->energies.size() ),
        energies, pdf, cdf,
        precompoundFraction, angularDistributionSlope
      )
    );
}
