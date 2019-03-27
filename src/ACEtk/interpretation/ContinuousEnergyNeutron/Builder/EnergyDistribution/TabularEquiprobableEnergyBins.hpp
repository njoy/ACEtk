struct TabularEquiprobableEnergyBins: 
  public Tabulated< details::verify::Positive< std::vector< double > > > {

  using Parent = Tabulated< details::verify::Positive< std::vector< double > > >;

  template< typename... Ts,
    utility::Require< true, std::is_constructible, Parent, Ts... > = true 
  >
  TabularEquiprobableEnergyBins( Ts&&... ts ) : 
    Parent( std::forward< Ts >( ts )... )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins/Builder.hpp"
};
