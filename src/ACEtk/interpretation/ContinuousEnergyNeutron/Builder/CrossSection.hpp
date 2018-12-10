struct CrossSection{
  Table::Slice energyGrid;
  details::verify::Positive< std::vector< double > > values;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder.hpp"
};
