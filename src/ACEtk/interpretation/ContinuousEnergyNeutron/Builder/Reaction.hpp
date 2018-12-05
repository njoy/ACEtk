struct Reaction{
 int MT;
 double Q;
 int neutronYield;
 Table::Slice energyGrid;
 details::verify::Positive< std::vector< double > > crossSection;
 // angularDistribution

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder.hpp"
};
