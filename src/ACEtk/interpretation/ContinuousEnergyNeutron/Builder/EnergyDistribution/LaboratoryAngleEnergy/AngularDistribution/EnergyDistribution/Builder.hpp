template< typename ParentBuilder >
class Builder {

  std::reference_wrapper< ParentBuilder > parent;

  std::optional< int > interpolationParameter_;
  std::optional< dvP< dvS< std::vector< double > > > > energies_;
  std::optional< details::verify::PDF< std::vector< double > > >  pdf_;
  std::optional< dvC< std::vector< double > > > cdf_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/src/construct.hpp"


public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/src/interpolationParameter.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/src/energies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/src/pdf.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution/Builder/src/cdf.hpp"

  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addEnergyDistribution( this->construct() );
  }
};
