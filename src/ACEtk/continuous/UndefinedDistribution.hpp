#ifndef NJOY_ACETK_CONTINUOUS_UNDEFINEDDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_UNDEFINEDDISTRIBUTION

// system includes

// other includes

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The distribution is undefined
 *
 *  The UndefinedDistribution class contains contains no data. It is a
 *  convenience interface object used in the DLWH block when no energy
 *  distribution data is given.
 */
class UndefinedDistribution {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  UndefinedDistribution() = default;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
