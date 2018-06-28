template< typename xRange, typename yRange >
class Region {
  int interpolationScheme_;
  xRange  x_;
  yRange  y_;

#include "ACEtk/interpretation/Region/src/verifyInterpolationScheme.hpp"

public:
#include "ACEtk/interpretation/Region/src/ctor.hpp"

  int interpolationScheme() const { return interpolationScheme_; }
  auto x() const { return x_; }
  auto y() const { return y_; }

};
