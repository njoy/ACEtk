struct AngularDistribution{

  class Builder;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable.hpp"

  using Format = std::variant<
    Isotropic,
    Equiprobable,
    Tabulated
  >;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder.hpp"

  dvP< 
    dvS< std::vector< double > > > energyGrid;
  std::vector< Format > representations;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/src/ACEify.hpp"
};
