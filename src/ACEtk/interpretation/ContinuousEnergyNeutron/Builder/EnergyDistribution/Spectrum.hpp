template< typename S >
struct Spectrum {

  Tabulated1D tabulatedEffectiveTemperature;
  S spectrum;

  Spectrum( Tabulated1D&& tab, S&& spectrum ):
    tabulatedEffectiveTemperature( std::move( tab ) ),
    spectrum( std::move( spectrum ) )
  { }


  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Spectrum/Builder.hpp"
};
