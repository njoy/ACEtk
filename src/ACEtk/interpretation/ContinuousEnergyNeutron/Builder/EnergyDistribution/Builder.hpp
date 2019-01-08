template<  typename ParentBuilder >
class Builder {
  // public Tabulated1D::Builder< Builder< ParentBuilder > >{

  // using BaseBuilder = Tabulated1D::Builder< Builder< ParentBuilder > >;

  std::optional< std::vector< double > > boundaries_;
  std::optional< std::vector< double > > schemes_;
  std::optional< std::vector< double > > energies_;
  std::vector< double > probabilities_;
  std::vector< LAWS > laws_;

protected:
  std::reference_wrapper< ParentBuilder > parent;

public:
public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/boundaries.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/schemes.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder/src/energies.hpp"
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  EnergyDistribution::DiscretePhotonEnergy::Builder 
  discretePhotonEnergy( double probability ){
    return { probability, *this };
  }

};
