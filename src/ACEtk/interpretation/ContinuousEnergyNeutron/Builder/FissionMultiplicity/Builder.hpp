class Builder {
private:

  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/fissionMultiplicity/Builder/src/ctor.hpp"

  Polynomial::Builder polynomial(){ return Polynomial::Builder{ *this }; }
  Tabulated::Builder tabulated(){ return Tabulated::Builder{ *this }; }
};
