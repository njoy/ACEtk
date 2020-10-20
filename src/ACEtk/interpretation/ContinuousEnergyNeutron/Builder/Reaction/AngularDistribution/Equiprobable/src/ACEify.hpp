void ACEify( Table::Data& tData, double& LC ){
  LC = tData.XSS().size() - tData.JXS( 9 ) + 2;

  details::ACEify( tData, this->cosineBins );
}
