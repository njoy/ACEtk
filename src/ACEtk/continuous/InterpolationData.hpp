#ifndef NJOY_ACETK_CONTINUOUS_INTERPOLATIONDATA
#define NJOY_ACETK_CONTINUOUS_INTERPOLATIONDATA

// system includes

// other includes
#include "ACEtk/base/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Interpolation data
 */
class InterpolationData : protected base::ColumnData {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/continuous/InterpolationData/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/InterpolationData/src/ctor.hpp"

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return this->N(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const { return this->NB(); }

  /**
   *  @brief Return whether or not the data is linear-linear interpolatable
   */
  bool isLinearLinear() const { return this->NB() == 0; }

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

  using Base::empty;
  using ColumnData::name;
  using ColumnData::length;
  using ColumnData::XSS;
  using ColumnData::begin;
  using ColumnData::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
