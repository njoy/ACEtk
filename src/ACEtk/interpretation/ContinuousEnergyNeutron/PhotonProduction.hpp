class PhotonProduction {

protected:
  Slice crossSection_;
  Slice outgoingEnergyGrid_;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/PhotonProduction/src/ctor.hpp"

  auto crossSection() const{ return crossSection_; }
  auto outgoingEnergyGrid() const{ 
    return outgoingEnergyGrid_
      | ranges::view::chunk( 20 ); 
  }
};
