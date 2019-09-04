template< typename Derived >
class Builder {

  std::optional< dvSP< dvS< std::vector< int > > > > boundaries_;
  std::optional< dvP< std::vector< int > > > schemes_;
  std::optional< std::vector< double > > x_;
  std::optional< std::vector< T > > y_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/energies.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/boundaries.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/schemes.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/x.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated/Builder/src/y.hpp"
};
