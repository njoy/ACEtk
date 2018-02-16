class Equiprobable {
  Slice energyGrid_;
  Slice boundaries_;

public:
  #include  "ACEtk/interpretation/ContinuousEnergyNeutron/angularDistribution/Equiprobable/src/ctor.hpp"

  auto boundaries() const{ return boundaries_; }
  auto energyGrid() const {
    return scaleBy( 1.0 * mega( electronVolts ) )( this->energyGrid_ );
  }
};
