#ifndef NJOY_ACETK_BLOCK_DETAILS_DISTRIBUTIONDATABASE
#define NJOY_ACETK_BLOCK_DETAILS_DISTRIBUTIONDATABASE

// system includes
#include <variant>

// other includes
#include "utility/overload.hpp"
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/details/ColumnData.hpp"
#include "ACEtk/block/InterpolationData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief Base class for distribution data as a function of values
 */
template< typename Derived, typename Distribution >
class BaseDistributionData : protected details::Base {

  /* fields */
  std::size_t locb_;
  std::size_t nc_;
  InterpolationData interpolation_;
  details::ColumnData values_;
  std::vector< Distribution > distributions_;

  /* auxiliary functions */
  #include "ACEtk/block/details/BaseDistributionData/src/verifyValueIndex.hpp"
  #include "ACEtk/block/details/BaseDistributionData/src/generateBlocks.hpp"
  #include "ACEtk/block/details/BaseDistributionData/src/verifySize.hpp"

protected:

  /* auxiliary functions */
  #include "ACEtk/block/details/BaseDistributionData/src/generateXSS.hpp"

  /* constructor */
  #include "ACEtk/block/details/BaseDistributionData/src/ctor.hpp"

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
   *  @brief Return the number of values in each column
   */
  std::size_t N() const { return this->values_.N(); }

  /**
   *  @brief Return the number of values in each column
   */
  std::size_t numberValues() const { return this->N(); }

  /**
   *  @brief Return the values for a given column index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] column    the column index (one-based)
   */
  auto values( std::size_t column ) const {

    return this->values_.column( column );
  }

  /**
   *  @brief Return the value for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] column    the column index (one-based)
   *  @param[in] index     the index (one-based)
   */
  double value( std::size_t column, std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyValueIndex( index );
    #endif
    return this->values_.value( column, index );
  }

  /**
   *  @brief Return the angular distribution locator for a value index
   *
   *  This locator is the value as stored in the XSS array.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LOCC( std::size_t index ) const {

    return this->value( this->nc_, index );
  }

  /**
   *  @brief Return the angular distribution locator for a value index
   *
   *  This locator is the value as stored in the XSS array.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int distributionLocator( std::size_t index ) const {

    return this->LOCC( index );
  }

  /**
   *  @brief Return the relative angular distribution locator for a value index
   *
   *  This is the locator relative to the beginning of the current distribution
   *  block.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t relativeDistributionLocator( std::size_t index ) const {

    const int locator = this->LOCC( index );
    return locator - this->locb_ + 1;
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< Distribution >& distributions() const {

    return this->distributions_;
  }

  /**
   *  @brief Return the distribution for a value index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const Distribution& distribution( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyValueIndex( index );
    #endif
    return this->distributions_[ index - 1 ];
  }

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
