void ACEify( Table::Data& tData, double& LC ){
  njoy::Log::info( "\t\tEquiprobable ACEify." );
  LC = tData.XSS().size() - tData.JXS( 9 ) + 1;

  details::ACEify( tData, this->cosineBins );
}
