struct TabularEnergyMultipliers: 
  public Tabulated< dvP< std::vector< double > > > {
  using Parent = Tabulated< dvP< std::vector< double > > >;

  using Tab = Tabulated< dvP< std::vector< double > > >;

  template< typename... Ts,
    utility::Require< true, std::is_constructible, Parent, Ts... > = true 
  >
  TabularEnergyMultipliers( Ts&&... ts ) : 
    Parent( std::forward< Ts >( ts )... )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEnergyMultipliers/Builder.hpp"

  void ACEify( Table::Data& tData, int ){
    Tab::ACEify( tData );
  }
};
