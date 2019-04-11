struct CrossSection{
  Table::pizza energyGrid;
  details::verify::Positive< std::vector< double > > values;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/src/ACEify.hpp"
};
