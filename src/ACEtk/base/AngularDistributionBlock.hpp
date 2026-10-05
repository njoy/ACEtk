#ifndef NJOY_ACETK_BASE_ANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_BASE_ANGULARDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/continuous/AngularDistributionData.hpp"
#include "ACEtk/continuous/FullyIsotropicDistribution.hpp"
#include "ACEtk/continuous/DistributionGivenElsewhere.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief Base class for angular distribution data, capable of accepting both a
 *         zero or one based reaction index
 */
class AngularDistributionBlock : protected Base {

public:

  /* type alias */

  using DistributionData = std::variant< continuous::FullyIsotropicDistribution,
                                         continuous::DistributionGivenElsewhere,
                                         continuous::AngularDistributionData >;

private:

  /* fields */

  unsigned int nr_;   // number of available reactions (excluding the zero index)
  Iterator iterator_; // the begin iterator of the actual data block
  std::vector< DistributionData > data_;
  bool zero_index_;

  /* auxiliary functions */

  static std::vector< DistributionData >
  insertZero( DistributionData&& zero, std::vector< DistributionData >&& data ) {

    data.insert( data.begin(), std::move( zero ) );
    return data;
  }

  static std::vector< double >
  generateXSS( std::vector< DistributionData >&& distributions ) {

    const auto nr = distributions.size();
    std::vector< double > xss( nr );
    std::size_t index = 0;
    for ( const auto& distribution : distributions ) {

      std::visit(

        tools::overload{

          [ &xss, index ] ( const continuous::FullyIsotropicDistribution& ) {

            xss[index] = 0;
          },
          [ &xss, index ] ( const continuous::DistributionGivenElsewhere& ) {

            xss[index] = -1;
          },
          [ &xss, index, nr ] ( const continuous::AngularDistributionData& value ) {

            xss[index] = xss.size() - nr + 1;

            // remake the internal xss array with the proper locators
            const continuous::AngularDistributionData temp(
                      std::move( value.distributions() ),
                      xss[index] );
            xss.insert( xss.end(), temp.begin(), temp.end() );
          }
        },
        distribution
      );
      ++index;
    }

    return xss;
  }

  void generateBlocks() {

    this->data_.clear();

    for ( unsigned int index = this->zero_index_ ? 0 : 1;
          index <= this->NR(); ++index ) {

      if ( this->isGiven( index ) ) {

        if ( this->isFullyIsotropic( index ) ) {

          this->data_.emplace_back( continuous::FullyIsotropicDistribution() );
        }
        else {

          // xand : one-based index to the start of the AND block
          // xand + locator - 1 : one-based index to the start of distribution data
          const std::size_t xand = std::distance( this->begin(), this->iterator_ ) + 1;
          const std::size_t land = this->LAND( index );
          const std::size_t locator = xand + land - 1;
          const auto left = this->iterator( locator );
          auto right = this->end();
          for ( auto next = index + 1; next <= this->NR(); ++next ) {

            const auto nextlocator = xand + this->LAND( next ) - 1;
            if ( nextlocator > locator ) {

              right = this->iterator( nextlocator );
              break;
            }
          }
          this->data_.emplace_back( continuous::AngularDistributionData( land, left, right ) );
        }
      }
      else {

        this->data_.emplace_back( continuous::DistributionGivenElsewhere() );
      }
    }
  }

  void verifySize( Iterator begin, Iterator data, Iterator,
                   unsigned int nr ) {

    // there are at least nr values in the locator block
    std::size_t size = std::distance( begin, data );
    std::size_t add = this->zero_index_ ? 1 : 0;
    if ( size < nr + add ) {

      if ( this->zero_index_ ) {

        Log::error( "The size of the XSS subrange in the locator part of the {} "
                    "block should be at least NR + 1", this->name() );
      }
      else {

        Log::error( "The size of the XSS subrange in the locator part of the {} "
                    "block should be at least NR", this->name() );
      }
      Log::info( "NR value: {}", nr );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  void verifyDataIndex( const std::size_t index ) const {

    if ( ( index < ( this->zero_index_ ? 0 : 1 ) ) || ( index > this->NR() ) ) {

      Log::error( "Illegal index argument into the {} block", this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between {} and {} inclusively",
                 this->name(), this->zero_index_ ? 0 : 1, this->NR() );
      throw std::out_of_range( this->name() );
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  AngularDistributionBlock( std::string&& name,
                            std::vector< DistributionData >&& xs,
                            std::size_t nr, bool zero ) :
    Base( std::move( name ), generateXSS( std::move( xs ) ) ),
    nr_( nr ), zero_index_( zero ) {

    this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
    this->generateBlocks();
  }

  /**
   *  @brief Private constructor
   */
  AngularDistributionBlock( std::string&& name,
                            DistributionData&& zero,
                            std::vector< DistributionData >&& data,
                            std::size_t nr ) :
    AngularDistributionBlock( std::move( name ),
                              insertZero( std::move( zero ),
                                          std::move( data ) ),
                              nr, true ) {}

protected:

  /* constructor */

  AngularDistributionBlock() = default;

  AngularDistributionBlock( const AngularDistributionBlock& base ) :
    Base( base ), nr_( base.nr_ ), iterator_( base.iterator_ ),
    data_( base.data_ ), zero_index_( base.zero_index_ ) {

    if ( Base::owner() ) {

      this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
      this->generateBlocks();
    }
  }

  AngularDistributionBlock( AngularDistributionBlock&& base ) :
    Base( std::move( base ) ), nr_( base.nr_ ), iterator_( base.iterator_ ),
    data_( std::move( base.data_ ) ), zero_index_( base.zero_index_ ) {

    if ( Base::owner() ) {

      this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
      this->generateBlocks();
    }
  }

  /**
   *  @brief Constructor for a block without a zero index
   *
   *  @param[in] name    the block name
   *  @param[in] data    the data
   */
  AngularDistributionBlock( std::string name, std::vector< DistributionData > data ) :
    AngularDistributionBlock( std::move( name ), std::move( data ),
                              data.size(), false ) {}

  /**
   *  @brief Constructor for a block with a zero index
   *
   *  @param[in] name    the block name
   *  @param[in] zero    the data for index zero
   *  @param[in] data    the data
   */
  AngularDistributionBlock( std::string name, DistributionData zero,
                                std::vector< DistributionData > data ) :
    AngularDistributionBlock( std::move( name ), std::move( zero ),
                              std::move( data ), data.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] name    the block name
   *  @param[in] loc     the begin iterator of the LSIG block in the XSS array
   *  @param[in] data    the begin iterator of the SIG block in the XSS array
   *  @param[in] end     the end iterator of the SIG block in the XSS array
   *  @param[in] nr     the number of reactions (excluding elastic)
   */
  AngularDistributionBlock( std::string name,
                            Iterator loc, Iterator data, Iterator end,
                            unsigned int nr, bool zero = false ) :
    Base( std::move( name ), loc, end ),
    nr_( nr ), iterator_( data ), zero_index_( zero ) {

    verifySize( this->begin(), this->iterator_, this->end(), this->nr_ );
    this->generateBlocks();
  }

  AngularDistributionBlock& operator=( const AngularDistributionBlock& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->nr_ = base.nr_;
      this->iterator_ = base.iterator_;
      this->data_ = base.data_;
      this->zero_index_ = base.zero_index_;
      if ( Base::owner() ) {

        this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
        this->generateBlocks();
      }
    }
    return *this;
  }

  AngularDistributionBlock& operator=( AngularDistributionBlock&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->nr_ = base.nr_;
      this->iterator_ = base.iterator_;
      this->data_ = std::move( base.data_ );
      this->zero_index_ = base.zero_index_;
      if ( Base::owner() ) {

        this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
        this->generateBlocks();
      }
    }
    return *this;
  }

  /* methods */

  /**
   *  @brief Return the number of available reactions (excluding the zero index)
   */
  unsigned int NR() const { return this->nr_; }

  /**
   *  @brief Return the number of available reactions (excluding the zero index)
   */
  unsigned int numberReactions() const { return this->NR(); }

  /**
   *  @brief Return the relative angular distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (zero or one-based)
   */
  int LAND( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyReactionIndex( index, this->zero_index_ ? 0 : 1, this->NR() );
    #endif
    std::size_t offset = this->zero_index_ ? 1 : 0;
    return this->IXSS( index + offset ); // elastic is index 0
  }

  /**
   *  @brief Return the relative angular distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (zero or one-based)
   */
  int angularDistributionLocator( std::size_t index ) const {

    return this->LAND( index );
  }

  /**
   *  @brief Return whether or not the distribution data is fully isotropic for
   *         a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (zero or one-based)
   */
  bool isFullyIsotropic( std::size_t index ) const {

    return this->LAND( index ) == 0;
  }

  /**
   *  @brief Return whether or not the distribution data for a reaction index
   *         is given in the AND block
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (zero or one-based)
   */
  bool isGiven( std::size_t index ) const {

    return this->LAND( index ) >= 0;
  }

  /**
   *  @brief Return the data vector
   */
  const std::vector< DistributionData >& data() const {

    return this->data_;
  }

  /**
   *  @brief Return the angular distribution data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DistributionData& angularDistributionData( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    std::size_t offset = this->zero_index_ ? 0 : 1;
    return this->data_[ index - offset ];
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
