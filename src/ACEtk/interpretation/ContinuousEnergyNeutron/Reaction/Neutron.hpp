class Neutron: protected Reaction {
public:
  Neutron( const Table& table, int ID ) :
    Reaction( table, ID, 
      Reaction::getReactionIndex( 
        ContinuousEnergyNeutron::neutronReactionIDs( table ), ID ) )
  { }

  using Reaction::ID;
  using Reaction::Index;
};
