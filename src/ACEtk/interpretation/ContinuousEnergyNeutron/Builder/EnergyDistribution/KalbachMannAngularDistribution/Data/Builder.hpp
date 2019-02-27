template< typename ParentBuilder >
class Builder {

  std::reference_wrapper< ParentBuilder > parent;

  std::optional< int > interpolationParameter_;
  std::optional< details::verify::Sorted< details::verify::Positive< 
      std::vector< double > > > > energies_;
  std::optional< details::verify::Positive< std::vector< double > > >  pdf_;
  std::optional< details::verify::CDF< std::vector< double > > > cdf_;
  std::vector< AngularDistribution > angularDistributions_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/addData.hpp"

  friend AngularDistribution::Builder< Builder< ParentBuilder > >;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/interpolationParameter.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/energies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/pdf.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Data/Builder/src/cdf.hpp"

  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addData( this->construct() );
  }

  AngularDistribution::Builder< Builder< ParentBuilder > > 
  angularDistribution(){
    return { *this };
  }
};
