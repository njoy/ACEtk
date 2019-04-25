void ACEify( Table::Data& tData, double& LC ){
  LC = -1.0*( tData.XSS().size() - tData.JXS( 9 ) + 1 );

  details::ACEify( tData, interpolationFlag );
  details::ACEify( tData, cosineGrid.size() );
  details::ACEify( tData, this->cosineGrid );
  details::ACEify( tData, this->PDF );
  details::ACEify( tData, this->CDF );
}
