struct CrossSection{
  Table::Pizza energyGrid;
  dvP< std::vector< double > > values;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/src/ACEify.hpp"
};
