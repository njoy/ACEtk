struct Tabulated1D {
  std::vector< double > boundaries;
  std::vector< double > schemes;
  std::vector< double > x;
  std::vector< double > y;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated1D/Builder.hpp"
};
