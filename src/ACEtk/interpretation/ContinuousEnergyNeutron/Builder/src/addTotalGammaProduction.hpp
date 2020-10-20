Builder& addTotalGammaProduction( TotalGammaProduction&& tgp ){
  this->totalGammaProduction_ = std::move( tgp );
  return *this;
}
