class Tabulated{

  int interpolationFlag;
  details::verify::Positive< std::vector< double > > cosineGrid;
  details::verify::PDF< std::vector< double > > PDF;
  details::verify::CDF< std::vector< double > > CDF;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder.hpp"
};
