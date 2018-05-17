class Tabulated {
  int interpolationFlag_;
  Slice cosineBins_;
  CoupledDensityFunctions densityFunctions;

public:
  #include  "ACEtk/interpretation/ContinuousEnergyNeutron/angularDistribution/Tabulated/src/ctor.hpp"

  int interpolationFlag() const{ return interpolationFlag_; }
  auto cosineBins() const{ return cosineBins_; }
  auto PDF() const{ return densityFunctions.PDF(); }
  auto CDF() const{ return densityFunctions.CDF(); }
};
