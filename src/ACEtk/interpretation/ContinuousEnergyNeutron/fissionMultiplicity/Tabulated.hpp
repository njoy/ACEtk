class Tabulated {
  std::optional< Slice > NBT;
  std::optional< Slice > INT;
  Slice energies_;
  Slice nubar_;

public:
#include "ACEtk/interpretation/ContinuousEnergyNeutron/fissionMultiplicity/Tabulated/src/ctor.hpp"
#include "ACEtk/interpretation/ContinuousEnergyNeutron/fissionMultiplicity/Tabulated/src/interpolationSchemes.hpp"
#include "ACEtk/interpretation/ContinuousEnergyNeutron/fissionMultiplicity/Tabulated/src/regions.hpp"

  auto energies() const{
    return scaleBy( 1.0*mega( electronVolts ) )( this->energies_ );
  }

  auto multiplicities() const{ return this->nubar_; }

};
