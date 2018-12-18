struct AngularDistribution{

  class Builder;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Isotropic.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable.hpp"

  using Format = std::variant<
      Isotropic,
      Equiprobable
      >;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Builder.hpp"

  details::verify::Positive< 
    details::verify::Sorted< std::vector< double > > > energyGrid;
  std::vector< Format > representations;
};
