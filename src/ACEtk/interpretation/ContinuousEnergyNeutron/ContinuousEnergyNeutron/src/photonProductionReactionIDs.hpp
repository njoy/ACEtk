static
auto photonProductionReactionIDs( const Table& ACETable) {
  return ACETable.data.XSS( ACETable.data.JXS(13), ACETable.data.NXS( 6 ) );
}

auto photonProductionReactionIDs() const{
  return photonProductionReactionIDs( this->table );
}

