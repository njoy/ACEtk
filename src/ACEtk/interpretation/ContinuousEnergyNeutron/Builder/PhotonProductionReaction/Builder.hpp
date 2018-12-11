class Builder {
private:

  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  std::reference_wrapper< ParentBuilder > parent;
  int MF;
  int MT;

  std::optional< ContinuousEnergyNeutron::Builder::Tabulated1D > yields_;
  std::optional< ContinuousEnergyNeutron::Builder::CrossSection > crossSection_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/addCrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/addYields.hpp"

  friend CrossSection::Builder;
  friend Yields::Builder;
  PhotonProductionReaction construct(){
    return PhotonProductionReaction{
      MT,
      yields_,
      crossSection_
    };
  }

public:
  Builder( ParentBuilder& parent, int MF, int MT ):
    parent( parent ),
    MF( MF ),
    MT( MT )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/yields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder/src/crossSection.hpp"
};
