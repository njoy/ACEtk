#ifndef NJOY_ACETK_BLOCK_DETAILS_BASETABULATEDDATA
#define NJOY_ACETK_BLOCK_DETAILS_BASETABULATEDDATA

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/details/ColumnData.hpp"
#include "ACEtk/block/InterpolationData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief Base class for energy distribution data as a function of incident energy
 */
class BaseTabulatedData : protected details::Base {

  /* fields */
  InterpolationData interpolation_;
  details::ColumnData data_;

  /* auxiliary functions */
  #include "ACEtk/block/details/BaseTabulatedData/src/generateXSS.hpp"
  #include "ACEtk/block/details/BaseTabulatedData/src/generateBlocks.hpp"
  #include "ACEtk/block/details/BaseTabulatedData/src/verifySize.hpp"

protected:

  /* constructor */
  #include "ACEtk/block/details/BaseTabulatedData/src/ctor.hpp"

public:

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
  using Base::begin;
  using Base::end;
};

} // details namespace
} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
