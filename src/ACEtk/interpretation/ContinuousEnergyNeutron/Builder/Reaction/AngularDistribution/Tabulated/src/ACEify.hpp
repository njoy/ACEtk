void ACEify( Table::Data& tData, double& LC ){
  njoy::Log::info( "\t\tTabulated ACEify." );
  LC = -1.0*( tData.XSS().size() - tData.JXS( 9 ) + 1 );

  Log::info( "\t\t\tinterpolationFlag: {}", interpolationFlag );
  details::ACEify( tData, interpolationFlag );
  Log::info( "\t\t\tcosineGrid.size(): {}", cosineGrid.size() );
  details::ACEify( tData, cosineGrid.size() );
  Log::info( "\t\t\tcosineGrid: {}", cosineGrid | ranges::view::all );
  details::ACEify( tData, this->cosineGrid );
  Log::info( "\t\t\tPDF: {}", PDF | ranges::view::all );
  details::ACEify( tData, this->PDF );
  Log::info( "\t\t\tCDF: {}", CDF | ranges::view::all );
  details::ACEify( tData, this->CDF );
  Log::info( "done with Tabulated." );
}
