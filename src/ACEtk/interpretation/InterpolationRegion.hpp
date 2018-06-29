template< typename xRange, typename yRange >
class InterpolationRegion {
  int interpolationScheme_;
  xRange  x_;
  yRange  y_;

#include "ACEtk/interpretation/InterpolationRegion/src/verifyInterpolationScheme.hpp"

public:
#include "ACEtk/interpretation/InterpolationRegion/src/ctor.hpp"
#include "ACEtk/interpretation/InterpolationRegion/src/makeInterpolationRegions.hpp"

  int interpolationScheme() const { return interpolationScheme_; }
  auto x() const { return x_; }
  auto y() const { return y_; }

};
