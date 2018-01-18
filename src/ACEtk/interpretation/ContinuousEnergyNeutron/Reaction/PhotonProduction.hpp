class PhotonProduction: protected Base {
public:
  PhotonProduction( const Table& table, int ID ):
    Base( table, ID,
      Base::getReactionIndex(
        ContinuousEnergyNeutron::photonProductionReactionIDs( table ), ID ) )
  { }

  using Base::ID;
  using Base::Index;
};
