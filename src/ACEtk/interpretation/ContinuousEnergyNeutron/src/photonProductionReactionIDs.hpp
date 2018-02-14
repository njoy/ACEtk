static
auto photonProductionReactionIDs( const Table& ACETable) {
  return ACETable.data.XSS( 
    ACETable.data.JXS( 
        ContinuousEnergyNeutron::PhotonProductionHeaderIndices::MTs.jxs ), 
    ACETable.data.NXS( 
        ContinuousEnergyNeutron::PhotonProductionHeaderIndices::MTs.nxs ) );
}

auto photonProductionReactionIDs() const{
  return photonProductionReactionIDs( this->table );
}

