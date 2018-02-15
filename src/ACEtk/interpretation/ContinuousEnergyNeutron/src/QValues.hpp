static
auto QValues( const Table& ACETable){

  int NMT = ACETable.data.NXS( NeutronHeaderIndices::QValues.nxs );
  int LQR = ACETable.data.JXS( NeutronHeaderIndices::QValues.jxs );

  return ACETable.data.XSS( LQR, NMT );
}

auto QValues() const{
  return QValues( this->table );
}
