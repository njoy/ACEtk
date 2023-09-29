#ifndef NJOY_ACETK_BASE_TABULATEDDATA
#define NJOY_ACETK_BASE_TABULATEDDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/ColumnData.hpp"
#include "ACEtk/block/InterpolationData.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief Base class for energy distribution data as a function of incident energy
 */
class TabulatedData : protected Base {

  /* fields */
  block::InterpolationData interpolation_;
  ColumnData data_;

  /* auxiliary functions */
  #include "ACEtk/base/TabulatedData/src/generateXSS.hpp"
  #include "ACEtk/base/TabulatedData/src/generateBlocks.hpp"
  #include "ACEtk/base/TabulatedData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/base/TabulatedData/src/ctor.hpp"

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const { return this->interpolation_; }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return this->interpolationData().NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const { return this->NB(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return this->interpolationData().NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return this->interpolationData().INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the number of elements
   */
  std::size_t N() const { return this->data_.N(); }

  /**
   *  @brief Return the number of elements
   */
  std::size_t numberElements() const { return this->N(); }

  /**
   *  @brief Return the x values
   */
  auto x() const { return this->data_.column( 1 ); }

  /**
   *  @brief Return the y values
   */
  auto y() const { return this->data_.column( 2 ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::IXSS;
  using Base::begin;
  using Base::end;
};

} // base namespace
} // ACEtk namespace
} // njoy namespace

#endif
