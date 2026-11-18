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

  static std::vector< std::vector< double > >
  generateXSS( std::vector< long >&& boundaries,
               std::vector< long >&& interpolants ) {

    std::vector< std::vector< double > > columns;
    columns.emplace_back( boundaries.begin(), boundaries.end() );
    columns.emplace_back( interpolants.begin(), interpolants.end() );
    return columns;
  }

public:

  /* constructor */

  InterpolationData() = default;

  InterpolationData( const InterpolationData& ) = default;
  InterpolationData( InterpolationData&& ) = default;

  InterpolationData& operator=( const InterpolationData& ) = default;
  InterpolationData& operator=( InterpolationData&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] name           the name of the data
   *  @param[in] boundaries     the interpolation range boundaries
   *  @param[in] interpolants   the interpolation types for each range
   */
  InterpolationData( std::string name,
                     std::vector< long > boundaries,
                     std::vector< long > interpolants ) :
    ColumnData( std::move( name ),
                generateXSS( std::move( boundaries ),
                             std::move( interpolants ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] name     the name of the data
   *  @param[in] begin    the begin iterator of the interpolation data
   *  @param[in] end      the end iterator of the interpolation data
   */
  InterpolationData( std::string name, Iterator begin, Iterator end ) :
    ColumnData( std::move( name ), begin, end, 2 ) {}

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
