struct CrossSection{
  int MT;
  Table::Slice energyGrid;
  details::verify::Positive< std::vector< double > > values;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/CrossSection/Builder.hpp"
};
