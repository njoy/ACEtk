template< typename T >
struct Tabulated {
  std::vector< double > boundaries;
  std::vector< double > schemes;
  std::vector< double > x;
  std::vector< T > y;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder.hpp"
};

using Tabulated1D = Tabulated< double >;
