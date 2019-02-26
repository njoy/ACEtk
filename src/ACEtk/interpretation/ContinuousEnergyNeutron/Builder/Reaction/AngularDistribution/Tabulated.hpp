struct Tabulated{

  int interpolationFlag;
  details::verify::CosineBins< std::vector< double > > cosineGrid;
  details::verify::Positive< std::vector< double > > PDF;
  details::verify::CDF< std::vector< double > > CDF;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/AngularDistribution/Tabulated/Builder.hpp"
};
