#ifndef NJOY_ACETK_BASE_ELECTRONBASEBLOCKWITHLOCATORS
#define NJOY_ACETK_BASE_ELECTRONBASEBLOCKWITHLOCATORS

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief The base class for a combined locator and data block prepended
 */
template < typename Derived, typename Data >
class ElectronBlockWithLocators : protected Base {

  /* fields */

  std::size_t n_;
  ArrayData information_;
  std::vector< Data > data_; // the data blocks

  /* auxiliary functions */

  static std::vector< double > generateXSS( std::vector< Data >&& blocks ) {

    const auto n = blocks.size();
    std::vector< double > energies( n );
    std::vector< double > lengths( n );
    std::vector< double > xss( n );

    std::size_t index = 0;
    for ( const auto& data : blocks ) {

      energies[index] = data.energy();
      lengths[index] = data.L();
      xss[index] = static_cast< double >( xss.size() - n );
      xss.insert( xss.end(), data.begin(), data.end() );
      ++index;
    }

    xss.insert( xss.begin(), lengths.begin(), lengths.end() );
    xss.insert( xss.begin(), energies.begin(), energies.end() );

    return xss;
  }

  void generateBlocks() {

    this->data_.clear();

    auto begin = this->begin();
    auto iter = std::next( begin, 3 * this->N() );
    this->information_ = ArrayData( "ELAS", begin, iter, this->N(), 3 );

    std::size_t data = std::distance( begin, iter ) + 1;
    for ( unsigned int index = 1; index <= this->N(); ++index ) {

      std::size_t locator = this->LLOC( index );
      const auto left = this->iterator( data + locator - 1 );
      const auto right = std::next( left, 2 * this->length( index ) );
      this->data_.emplace_back( this->energy( index ), left, right, this->length( index ) );
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  ElectronBlockWithLocators( std::string&& name, std::vector< Data >&& xs,
                             std::size_t n ) :
    Base( std::move( name ), Derived::generateXSS( std::move( xs ) ) ), n_( n ) {

    static_cast< Derived* >( this )->generateBlocks();
  }

protected:

  /* auxiliary functions */

  void verifyDataIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->N() ) ) {

      Log::error( "Illegal index argument into the {} block", this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between 1 and {} inclusively",
                 this->name(), this->N() );
      throw std::out_of_range( this->name() );
    }
  }

  /* constructor */

  ElectronBlockWithLocators() = default;

  ElectronBlockWithLocators( const ElectronBlockWithLocators& base ) :
    Base( base ), n_( base.n_ ), information_( base.information_ ),
    data_( base.data_ ) {

    if ( Base::owner() ) {

      static_cast< Derived* >( this )->generateBlocks();
    }
  }

  ElectronBlockWithLocators( ElectronBlockWithLocators&& base ) :
    Base( std::move( base ) ), n_( base.n_ ),
    information_( std::move( base.information_ ) ), data_( std::move( base.data_ ) ) {

    if ( Base::owner() ) {

      static_cast< Derived* >( this )->generateBlocks();
    }
  }

  /**
   *  @brief Constructor for a block
   *
   *  @param[in] name    the block name
   *  @param[in] data    the data
   */
  ElectronBlockWithLocators( std::string name, std::vector< Data > data ) :
    ElectronBlockWithLocators( std::move( name ), std::move( data ), data.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] name     the block name
   *  @param[in] begin    the begin iterator of the block in the XSS array
   *  @param[in] end      the end iterator of the SIG block in the XSS array
   *  @param[in] n        the number of reactions (excluding elastic)
   */
  ElectronBlockWithLocators( std::string name, Iterator begin, Iterator end,
                             unsigned int n ) :
    Base( std::move( name ), begin, end ), n_( n ) {

    static_cast< Derived* >( this )->generateBlocks();
  }

  ElectronBlockWithLocators& operator=( const ElectronBlockWithLocators& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->n_ = base.n_;
      this->information_ = base.information_;
      this->data_ = base.data_;
      if ( Base::owner() ) {

        static_cast< Derived* >( this )->generateBlocks();
      }
    }
    return *this;
  }

  ElectronBlockWithLocators& operator=( ElectronBlockWithLocators&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->n_ = base.n_;
      this->information_ = std::move( base.information_ );
      this->data_ = std::move( base.data_ );
      if ( Base::owner() ) {

        static_cast< Derived* >( this )->generateBlocks();
      }
    }
    return *this;
  }

public:

  /* methods */

  /**
   *  @brief Return the number of available data blocks
   */
  unsigned int N() const { return this->n_; }

  /**
   *  @brief Return the number of available data blocks
   */
  unsigned int numberDataBlocks() const { return this->N(); }

  /**
   *  @brief Return the relative data locator for a data block index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LLOC( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->information_.ivalue( 3, index ) + 1;
  }

  /**
   *  @brief Return the relative data locator for a data block index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t locator( std::size_t index ) const {

    return this->LLOC( index );
  }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return this->information_.darray( 1 ); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the table lengths
   */
  auto L() const { return this->information_.iarray( 1 ); }

  /**
   *  @brief Return the table lengths
   */
  auto lengths() const { return this->L(); }

  /**
   *  @brief Return the data vector
   */
  const std::vector< Data >& data() const {

    return this->data_;
  }

  /**
   *  @brief Return the energy for a data block index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double energy( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->information_.dvalue( 1, index );
  }

  /**
   *  @brief Return the table length for a data block index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int length( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->information_.ivalue( 2, index );
  }

  /**
   *  @brief Return the data for a data block index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const Data& data( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->data_[ index - 1 ];
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
