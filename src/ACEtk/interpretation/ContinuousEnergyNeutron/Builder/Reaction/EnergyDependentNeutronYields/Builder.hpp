class Builder: public Tabulated1D::Builder< Builder > {
private:
  using TabBuilder = Tabulated1D::Builder< Builder >;

  using ParentBuilder = Reaction::Builder;

  std::reference_wrapper< ParentBuilder > parent;

protected:

  using TabBuilder::construct;

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add(){
    return parent.get().addEnergyDependentNeutronYields( this->construct() );
  }

  using TabBuilder::TabBuilder;
  using TabBuilder::energies;
  using TabBuilder::boundaries;
  using TabBuilder::schemes;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/EnergyDependentNeutronYields/Builder/src/yields.hpp"
};
