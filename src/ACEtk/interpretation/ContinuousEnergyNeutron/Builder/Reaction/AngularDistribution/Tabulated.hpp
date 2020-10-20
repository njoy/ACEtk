struct Tabulated{

  int interpolationFlag;
  dvCB< std::vector< double > > cosineGrid;
  dvP< std::vector< double > > PDF;
  dvC< std::vector< double > > CDF;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/src/ACEify.hpp"
};
