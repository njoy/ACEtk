void ACEify( Table::Data& tData, int ){
  
  tData.XSS().push_back( 
    ( atomicWeightRatio + 1 )/atomicWeightRatio*abs( QValue ) );
  tData.XSS().push_back( 
    std::pow( double( atomicWeightRatio/( atomicWeightRatio + 1 ) ), 2 ) );
}
