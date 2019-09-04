template< typename T >
struct Tabulated {
  using opt_t = std::pair< 
      dvSP< dvS< std::vector< int > > >,
      dvP< std::vector< int > > >;
  std::optional<  opt_t > parameters;
  std::vector< double > x;
  std::vector< T > y;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/src/ACEify.hpp"
};

using Tabulated1D = Tabulated< double >;
