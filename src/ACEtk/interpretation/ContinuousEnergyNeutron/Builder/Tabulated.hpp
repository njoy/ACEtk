template< typename T >
struct Tabulated {
  std::optional< std::pair<
      std::vector< double >,
      std::vector< double > > > parameters;
  std::vector< double > x;
  std::vector< T > y;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder.hpp"
};

using Tabulated1D = Tabulated< double >;
