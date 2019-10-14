template< typename ParentBuilder >
class Builder {

  std::reference_wrapper< ParentBuilder > parent;

  std::optional< int > interpolationParameter_;
  std::optional< int > numberDiscretePhotonLines_;
  std::optional< dvP< dvS< std::vector< double > > > > energies_;
  std::optional< dvP< std::vector< double > > >  pdf_;
  std::optional< dvC< std::vector< double > > > cdf_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/construct.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/interpolationParameter.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/numberDiscretePhotonLines.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/energies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/pdf.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/ContinuousTabularDistribution/Data/Builder/src/cdf.hpp"

  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addData( this->construct() );
  }
};
