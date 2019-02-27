template< typename ParentBuilder >
class Builder {

  std::reference_wrapper< ParentBuilder > parent;

  std::optional< int > interpolationParameter_;
  std::optional< details::verify::Sorted< details::verify::Positive< 
      std::vector< double > > > > energies_;
  std::optional< details::verify::Positive< std::vector< double > > >  pdf_;
  std::optional< details::verify::CDF< std::vector< double > > > cdf_;
  std::optional< std::vector< double > > precompoundFraction_;
  std::optional< std::vector< double > > angularDistributionSlope_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/construct.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/interpolationParameter.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/energies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/pdf.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/cdf.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/precompoundFraction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMann/Data/Builder/src/angularDistributionSlope.hpp"

  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add() {
    return parent.get().addData( this->construct() );
  }
};
