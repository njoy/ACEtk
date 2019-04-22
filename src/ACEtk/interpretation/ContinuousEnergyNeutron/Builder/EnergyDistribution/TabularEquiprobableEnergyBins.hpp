struct TabularEquiprobableEnergyBins: 
  public Tabulated< dvP< std::vector< double > > > {

  using Parent = Tabulated< dvP< std::vector< double > > >;

  template< typename... Ts,
    utility::Require< true, std::is_constructible, Parent, Ts... > = true 
  >
  TabularEquiprobableEnergyBins( Ts&&... ts ) : 
    Parent( std::forward< Ts >( ts )... )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins/Builder.hpp"

  void ACEify( Table::Data& tData, int ){
    return Parent::ACEify( tData );
  }
};
