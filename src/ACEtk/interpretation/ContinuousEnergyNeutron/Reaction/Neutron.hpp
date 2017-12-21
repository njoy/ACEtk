class Neutron: protected Base {
public:
  Neutron( const Table& table, int ID ) :
    Base( table, ID, 
      Base::getReactionIndex( 
        ContinuousEnergyNeutron::neutronReactionIDs( table ), ID ) )
  { }
};
