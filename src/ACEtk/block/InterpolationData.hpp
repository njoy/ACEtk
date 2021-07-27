#ifndef NJOY_ACETK_BLOCK_INTERPOLATIONDATA
#define NJOY_ACETK_BLOCK_INTERPOLATIONDATA

// system includes

// other includes
#include "ACEtk/block/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Interpolation data
 */
class InterpolationData : protected ColumnData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/InterpolationData/src/ctor.hpp"

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return this->N(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const { return this->NB(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return this->column( 1 ); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return this->column( 2 ); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->INT(); }

  using ColumnData::name;
  using ColumnData::length;
  using ColumnData::XSS;
  using ColumnData::begin;
  using ColumnData::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
