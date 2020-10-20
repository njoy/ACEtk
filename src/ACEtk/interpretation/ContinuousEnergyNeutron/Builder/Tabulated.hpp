template< typename T >
struct Tabulated {
  using opt_t = std::pair< 
      dvSP< dvS< std::vector< int > > >,
      std::vector< int > >;
  std::optional<  opt_t > parameters;
  dvS< std::vector< double > > x;
  std::vector< T > y;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/src/ACEify.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/src/ACEifyNoty.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/src/ACEifywithNET.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/src/ACEifywithLOC.hpp"
};

using Tabulated1D = Tabulated< double >;
