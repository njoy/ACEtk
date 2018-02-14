class Reaction {
protected: 
  ContinuousEnergyNeutron::CrossSection crossSection_;

public:

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Reaction/src/ctor.hpp"

  CrossSection crossSection() const{
    return crossSection_;
  }
};

