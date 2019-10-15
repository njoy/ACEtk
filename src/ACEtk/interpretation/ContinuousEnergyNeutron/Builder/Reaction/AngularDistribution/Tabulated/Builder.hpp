class Builder {

  using ParentBuilder = ContinuousEnergyNeutron::Builder::Reaction::
      AngularDistribution::Builder;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< int > interpolationFlag_;
  std::optional< dvCB< std::vector< double > > > cosineGrid_;
  std::optional< dvP< std::vector< double > > > PDF_;
  std::optional< dvC< std::vector< double > > > CDF_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/equalSize.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addTabulated( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/pdf.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/cdf.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/cosineGrid.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/interpolationFlag.hpp"
};
