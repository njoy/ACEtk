class Tabulated {
  Slice energyGrid_;

public:
  #include  "ACEtk/interpretation/ContinuousEnergyNeutron/angularDistribution/Tabulated/src/ctor.hpp"

  auto energyGrid() const {
    return scaleBy( 1.0 * mega( electronVolts ) )( this->energyGrid_ );
  }
};
