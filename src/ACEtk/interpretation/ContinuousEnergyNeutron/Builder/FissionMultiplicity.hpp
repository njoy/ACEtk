struct FissionMultiplicity {
  class Builder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Polynomial.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Tabulated.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Builder.hpp"
};
using Nubar = std::variant< FissionMultiplicity::Polynomial, 
                            FissionMultiplicity::Tabulated >;
