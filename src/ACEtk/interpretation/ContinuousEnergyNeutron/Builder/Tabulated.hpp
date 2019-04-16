template< typename T >
struct Tabulated {
  std::optional< 
    std::pair<
      std::vector< int >,
      std::vector< int > > > parameters;
  std::vector< double > x;
  std::vector< T > y;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/src/ACEify.hpp"
};

using Tabulated1D = Tabulated< double >;
