template< typename Derived >
class Builder {

  std::optional< std::vector< double > > boundaries_;
  std::optional< std::vector< double > > schemes_;
  std::optional< std::vector< double > > x_;
  std::optional< std::vector< double > > y_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated1D/Builder/src/construct.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated1D/Builder/src/boundaries.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated1D/Builder/src/schemes.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated1D/Builder/src/x.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated1D/Builder/src/y.hpp"
};

