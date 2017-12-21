static
auto neutronReactionIDs(const Table& ACETable) {
  return ACETable.data.XSS( ACETable.data.JXS(3), ACETable.data.NXS( 4 ) );
}

auto neutronReactionIDs() const{
  return neutronReactionIDs( this->table );
}
