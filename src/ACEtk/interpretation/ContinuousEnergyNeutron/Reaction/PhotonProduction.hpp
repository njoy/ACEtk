class PhotonProduction: protected Reaction {
public:
  PhotonProduction( const Table& table, int ID ):
    Reaction( table, ID,
      Reaction::getReactionIndex(
        ContinuousEnergyNeutron::photonProductionReactionIDs( table ), ID ) )
  { }

  using Reaction::ID;
  using Reaction::Index;
};
