static auto reactionIDs( const Table& ACETable) {
  return ranges::view::concat(
    ContinuousEnergyNeutron::neutronReactionIDs( ACETable ),
    ContinuousEnergyNeutron::photonProductionReactionIDs( ACETable )
    );
}

auto reactionIDs() const{
  return reactionIDs( this->table );
}
