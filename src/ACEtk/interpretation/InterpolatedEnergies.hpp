class InterpolatedEnergies {
protected:
  ENDFInterpolationParameters interpolationParameters_;
  Table::Slice incidentEnergies_;

public:
#include "ACEtk/interpretation/InterpolatedEnergies/src/ctor.hpp"

  auto interpolationParameters() const { return interpolationParameters_; }
  auto incidentEnergies() const{
    return scaleBy( 1.0*mega( electronVolts ) )( this->incidentEnergies_ );
  }
};
