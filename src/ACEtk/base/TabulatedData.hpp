#ifndef NJOY_ACETK_BASE_TABULATEDDATA
#define NJOY_ACETK_BASE_TABULATEDDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/ColumnData.hpp"
#include "ACEtk/continuous/InterpolationData.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief Base class for energy distribution data as a function of incident energy
 */
class TabulatedData : protected Base {

  /* fields */

  continuous::InterpolationData interpolation_;
  ColumnData data_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( const std::string& name,
               std::vector< long >&& boundaries,
               std::vector< long >&& interpolants,
               std::vector< double >&& x,
               std::vector< double >&& y ) {

    // reserve size in the vector
    std::vector< double > xss;
    const auto nr = boundaries.size();
    const auto ne = x.size();
    xss.reserve( 2 + 2 * nr + 2 * ne );

    // insert the interpolation data
    const continuous::InterpolationData interpolation( std::string( name ),
                                                       std::move( boundaries ),
                                                       std::move( interpolants ) );
    xss.insert( xss.end(), interpolation.begin(), interpolation.end() );

    // insert the tabulated data
    const ColumnData table( std::string( name ), std::move( x ), std::move( y ) );
    xss.insert( xss.end(), table.begin(), table.end() );

    return xss;
  }

  void generateBlocks() {

    const auto nr = static_cast< std::size_t >( this->IXSS( 1 ) );
    const auto ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
    const auto begin = this->begin();
    const auto data = begin + 2 * nr + 1;
    const auto end = data + 2 * ne + 1;

    this->interpolation_ = continuous::InterpolationData( this->name(), begin, data );
    this->data_ = ColumnData( this->name(), data, end, 2 );
  }

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int nr, unsigned int ne ) {

    // there are at least 2 + 2 * nr + 2 * ne values in the tabulated data block
    auto size = std::distance( begin, end );
    if ( size < 2 + 2 * nr + 2 * ne ) {

      Log::error( "The size of the XSS subrange in the tabulated data "
                  "block should be at least 2 + 2 * NR + 2 * NE" );
      Log::info( "NR value: {}", nr );
      Log::info( "NE value: {}", ne );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

public:

  /* constructor */

  TabulatedData() = default;

  TabulatedData( const TabulatedData& base ) :
    Base( base ), interpolation_( base.interpolation_ ),
    data_( base.data_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  TabulatedData( TabulatedData&& base ) :
    Base( std::move( base ) ), interpolation_( std::move( base.interpolation_ ) ),
    data_( std::move( base.data_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] name            the name of the block
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] x               the x values
   *  @param[in] y               the y values
   */
  TabulatedData( std::string name, std::vector< long > boundaries,
                 std::vector< long > interpolants, std::vector< double > x,
                 std::vector< double > y ) :
    Base( std::move( name ),
          generateXSS( name,
                       std::move( boundaries ), std::move( interpolants ),
                       std::move( x ), std::move( y ) ) ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] name    the name of the block
   *  @param[in] sig     the begin iterator of the block in the XSS array
   *  @param[in] end     the end iterator of the block in the XSS array
   */
  TabulatedData( std::string name, Iterator begin, Iterator end ) :
    Base( std::move( name ), begin, end ) {

    const auto nr = static_cast< std::size_t >( std::round( this->XSS( 1 ) ) );
    const auto ne = static_cast< std::size_t >( std::round( this->XSS( 1 + 2 * nr + 1 ) ) );
    verifySize( this->begin(), this->end(), nr, ne );
    this->generateBlocks();
  }

  TabulatedData& operator=( const TabulatedData& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->interpolation_ = base.interpolation_;
      this->data_ = base.data_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  TabulatedData& operator=( TabulatedData&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->interpolation_ = std::move( base.interpolation_ );
      this->data_ = std::move( base.data_ );
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

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
