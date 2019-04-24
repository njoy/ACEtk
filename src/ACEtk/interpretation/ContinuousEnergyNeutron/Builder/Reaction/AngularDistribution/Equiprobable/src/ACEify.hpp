void ACEify( Table::Data& tData, double& LC ){
  LC = tData.XSS().size() - tData.JXS( 9 ) + 1;

  details::ACEify( tData, this->cosineBins );
}
