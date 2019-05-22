struct Table{

  dvC< std::vector< double > > CDFs;
  dvP< std::vector< double > > totalCrossSections;
  dvP< std::vector< double > > elasticCrossSections;
  dvP< std::vector< double > > fissionCrossSections;
  dvP< std::vector< double > > captureCrossSections;
  dvP< std::vector< double > > heating;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/ProbabilityTable/Table/src/ACEify.hpp"
};
