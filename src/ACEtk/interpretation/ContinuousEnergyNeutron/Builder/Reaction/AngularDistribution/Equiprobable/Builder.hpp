class Builder {

  using ParentBuilder = ContinuousEnergyNeutron::Builder::Reaction::
      AngularDistribution::Builder;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< 
    details::verify::Sorted< std::array< double, 33 > > > cosineBins_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable/Builder/src/construct.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Equiprobable/Builder/src/cosineBins.hpp"
};
