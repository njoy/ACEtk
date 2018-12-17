class Builder {

  using ParentBuilder = ContinuousEnergyNeutron::Builder::Reaction::Builder::
      AngularDistribution::Builder;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< int > interpolationFlag_;
  std::optional< 
    details::verify::Positive< std::vector< double > > > cosineGrid_;
  std::optional< details::verify::PDF< std::vector< double > > > PDF_;
  std::optional< details::verify::CDF< std::vector< double > > > CDF_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/equalSize.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/PDF.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder/src/CDF.hpp"
};
