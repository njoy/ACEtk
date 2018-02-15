class Polynomial {
  Slice coefficients_;

public:
  #include  "ACEtk/interpretation/ContinuousEnergyNeutron/fissionMultiplicity/Polynomial/src/ctor.hpp"

  auto coefficients() const { return coefficients_; }
};
