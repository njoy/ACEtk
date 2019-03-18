class Builder {
private:

  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  std::reference_wrapper< ParentBuilder > parent;
  std::string nuType;

public:
  Builder( ParentBuilder& parent, std::string nuType ): 
    parent( parent ),
    nuType( nuType )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Builder/src/polynomial.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Builder/src/tabulated.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Builder/src/precursors.hpp"

};
