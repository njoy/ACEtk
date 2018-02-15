class Reaction {
protected: 
  ContinuousEnergyNeutron::CrossSection crossSection_;
  double QValue_;

public:

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Reaction/src/ctor.hpp"

  CrossSection crossSection() const{ return crossSection_; }

  double QValue() const{ return QValue_; }
};

