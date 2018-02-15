struct fissionMultiplicity {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/fissionMultiplicity/Polynomial.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/fissionMultiplicity/Tabulated.hpp"
};

using FissionMultiplicity = std::variant< fissionMultiplicity::Polynomial, 
                                          fissionMultiplicity::Tabulated >;
