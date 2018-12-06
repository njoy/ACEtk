class Builder {
private:

  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  std::reference_wrapper< ParentBuilder > parent;
  int MF;
  int MT;

public:
  Builder( ParentBuilder& parent, int MF, int MT ):
    parent( parent ),
    MF( MF ),
    MT( MT )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/Builder/src/yields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/Builder/src/crossSection.hpp"
};
