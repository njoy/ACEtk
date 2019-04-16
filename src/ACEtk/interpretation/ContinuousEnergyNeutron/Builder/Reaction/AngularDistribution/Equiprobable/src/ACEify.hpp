void ACEify( Table::Data& tData, double& LC ){
  LC = 1;

  details::ACEify( tData, this->cosineBins );
}
