class Equiprobable {
  Slice boundaries_;

public:
  #include  "ACEtk/interpretation/ContinuousEnergyNeutron/AngularDistribution/Equiprobable/src/ctor.hpp"

  auto boundaries() const{ return boundaries_; }
};
