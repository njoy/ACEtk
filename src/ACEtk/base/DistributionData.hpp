#ifndef NJOY_ACETK_BASE_DISTRIBUTIONDATABASE
#define NJOY_ACETK_BASE_DISTRIBUTIONDATABASE

// system includes
#include <variant>

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/ColumnData.hpp"
#include "ACEtk/continuous/InterpolationData.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief Base class for distribution data as a function of values using
 *         ENDF style interpolation data
 */
template< typename Derived, typename Distribution >
class DistributionData : protected Base {

  /* fields */

  std::size_t locb_;

protected:

  continuous::InterpolationData interpolation_;
  ColumnData values_;
  std::vector< Distribution > distributions_;

private:

  /* auxiliary functions */

  void verifyValueIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->numberValues() ) ) {

      Log::error( "Illegal index argument into {} block",
                  this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between 1 and {} inclusively",
                 this->name(), this->numberValues() );
      throw std::out_of_range( this->name() );
    }
  }

  void generateBlocks() {

    this->distributions_.clear();

    const auto nr = static_cast< std::size_t >( this->IXSS( 1 ) );
    const auto ne = static_cast< std::size_t >( this->IXSS( 2 + 2 * nr ) );
    auto begin = this->begin();
    auto data = this->iterator( 2 + 2 * nr );
    auto end = this->iterator( 2 + 2 * nr + 2 * ne + 1 );

    this->interpolation_ = continuous::InterpolationData( this->name(), begin, data );
    this->values_ = ColumnData( this->name(), data, end, 2 );
    for ( unsigned int index = 1; index <= this->numberValues(); ++index ) {

      const double value = this->value( 1, index );
      const auto locb = this->distributionLocator( index );
      const auto locator = this->relativeDistributionLocator( index );
      const auto left = this->iterator( locator );
      auto right = this->end();
      for ( auto next = index + 1; next <= this->numberValues(); ++next ) {

        auto nextlocator = this->relativeDistributionLocator( next );
        if ( nextlocator > locator ) {

          right = this->iterator( nextlocator );
          break;
        }
      }
      this->distributions_.emplace_back( Distribution( value, locb, left, right ) );
    }
  }

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int nr, unsigned int ne ) {

    // there are at least 2 + 2 * nr + 2 * ne values in the distribution data block
    auto size = std::distance( begin, end );
    if ( size < 2 + 2 * nr + 2 * ne ) {

      Log::error( "The size of the XSS subrange in the distribution data "
                  "block should be at least 2 + 2 * NR + 2 * NE" );
      Log::info( "NR value: {}", nr );
      Log::info( "NE value: {}", ne );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

protected:

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( const std::string& name,
               std::vector< long >&& boundaries,
               std::vector< long >&& interpolants,
               std::vector< Distribution >&& distributions,
               std::size_t locb ) {

    // add the distribution data to the xss array
    const auto nr = boundaries.size();
    const auto ne = distributions.size();
    std::vector< double > xss( 1 + 2 * ne );
    xss[0] = ne;
    std::size_t index = 1;
    const auto offset = 1 + 2 * nr + locb;
    for ( const auto& distribution : distributions ) {

      // set the associated value
      xss[index] = distribution.value();

      // set the locator
      xss[index + ne] = static_cast< double >( xss.size() + offset );

      // insert the xss array
      xss.insert( xss.end(), distribution.begin(), distribution.end() );

      // on to the next distribution
      ++index;
    }

    // insert the interpolation data in the front
    const continuous::InterpolationData interpolation( std::string( name ),
                                                       std::move( boundaries ),
                                                       std::move( interpolants ) );
    xss.insert( xss.begin(), interpolation.begin(), interpolation.end() );

    return xss;
  }

  /* constructor */

  DistributionData() = default;

  DistributionData( const DistributionData& base ) :
    Base( base ), locb_( base.locb_ ),
    interpolation_( base.interpolation_ ),
    values_( base.values_ ),
    distributions_( base.distributions_ ) {

    if ( Base::owner() ) {

      static_cast< Derived* >( this )->generateBlocks();
    }
  }

  DistributionData( DistributionData&& base ) :
    Base( std::move( base ) ), locb_( base.locb_ ),
    interpolation_( std::move( base.interpolation_ ) ),
    values_( std::move( base.values_ ) ),
    distributions_( std::move( base.distributions_ ) ) {

    if ( Base::owner() ) {

      static_cast< Derived* >( this )->generateBlocks();
    }
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] name             the name of the block
   *  @param[in] boundaries       the interpolation range boundaries
   *  @param[in] interpolants     the interpolation types for each range
   *  @param[in] distributions    the distributions for each incident energy
   *  @param[in] locb             the starting xss index with respect to the superblock
   */
  DistributionData( std::string name,
                    std::vector< long > boundaries,
                    std::vector< long > interpolants,
                    std::vector< Distribution > distributions,
                    std::size_t locb ) :
    Base( std::move( name ),
          Derived::generateXSS( std::string( name ),
                                std::move( boundaries ), std::move( interpolants ),
                                std::move( distributions ), locb ) ),
    locb_( locb ) {

    static_cast< Derived* >( this )->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] name    the name of the block
   *  @param[in] locb    the starting xss index with respect to the superblock
   *  @param[in] sig     the begin iterator of the block in the XSS array
   *  @param[in] end     the end iterator of the block in the XSS array
   */
  DistributionData( std::string name, std::size_t locb,
                    Iterator begin, Iterator end ) :
    Base( std::move( name ), begin, end ), locb_( locb ) {

    const auto nr = static_cast< std::size_t >( std::round( this->XSS( 1 ) ) );
    const auto ne = static_cast< std::size_t >( std::round( this->XSS( 1 + 2 * nr + 1 ) ) );
    verifySize( this->begin(), this->end(), nr, ne );
    static_cast< Derived* >( this )->generateBlocks();
  }

  DistributionData& operator=( const DistributionData& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->interpolation_ = base.interpolation_;
      this->values_ = base.values_;
      this->distributions_ = base.distributions_;
      this->locb_ = base.locb_;
      if ( Base::owner() ) {

        static_cast< Derived* >( this )->generateBlocks();
      }
    }
    return *this;
  }

  DistributionData& operator=( DistributionData&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->interpolation_ = std::move( base.interpolation_ );
      this->values_ = std::move( base.values_ );
      this->distributions_ = std::move( base.distributions_ );
      this->locb_ = base.locb_;
      if ( Base::owner() ) {

        static_cast< Derived* >( this )->generateBlocks();
      }
    }
    return *this;
  }

public:

  /**
   *  @brief Return the interpolation data
   */
  const continuous::InterpolationData& interpolationData() const {

    return this->interpolation_;
  }

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
   *  @brief Return the distribution locator for a value index
   *
   *  This locator is the value as stored in the XSS array.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LOCC( std::size_t index ) const {

    return static_cast< int >( std::round( this->value( this->values_.NC(),
                                                        index ) ) );
  }

  /**
   *  @brief Return the distribution locator for a value index
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
   *  @brief Return the relative distribution locator for a value index
   *
   *  This is the locator relative to the beginning of the current distribution
   *  block.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int relativeDistributionLocator( std::size_t index ) const {

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
  using Base::IXSS;
  using Base::begin;
  using Base::end;
};

} // base namespace
} // ACEtk namespace
} // njoy namespace

#endif
