static
auto neutronReactionIDs(const Table& ACETable) {
  return ACETable.data.XSS( 
    ACETable.data.JXS( ContinuousEnergyNeutron::NeutronHeaderIndices::MTs.jxs ), 
    ACETable.data.NXS( ContinuousEnergyNeutron::NeutronHeaderIndices::MTs.nxs ) );
}

auto neutronReactionIDs() const{
  return neutronReactionIDs( this->table );
}
