template< typename ParentBuilder >
class Builder {

  std::reference_wrapper< ParentBuilder > parent;

  std::optional< int > interpolationParameter_;
  std::optional< dvCB< std::vector< double > > > cosines_;
  std::vector< EnergyDistribution > energyDistributions_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder/src/addEnergyDistribution.hpp"

  friend EnergyDistribution::Builder< Builder< ParentBuilder > >;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder/src/interpolationParameter.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder/src/cosines.hpp"

  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addAngularDistribution( this->construct() );
  }

  EnergyDistribution::Builder< Builder< ParentBuilder > > 
  energyDistribution(){ return { *this }; }
};

