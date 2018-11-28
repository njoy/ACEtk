struct fissionMultiplicity {
  class Builder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/fissionMultiplicity/Polynomial.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/fissionMultiplicity/Tabulated.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/fissionMultiplicity/Builder.hpp"
};

using FissionMultiplicity = std::variant< fissionMultiplicity::Polynomial, 
                                          fissionMultiplicity::Tabulated >;
