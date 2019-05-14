class Builder: public Tabulated1D::Builder< Builder > {
private:
  using TabBuilder = Tabulated1D::Builder< Builder >;

  using ParentBuilder = Reaction::Builder;

  std::reference_wrapper< ParentBuilder > parent;

protected:
  friend Reaction::Builder;

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  using TabBuilder::TabBuilder;
  using TabBuilder::energies;
  using TabBuilder::boundaries;
  using TabBuilder::schemes;
  using TabBuilder::construct;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/EnergyDependentNeutronYields/Builder/src/yields.hpp"
};
