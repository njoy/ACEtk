#ifndef NJOY_ACETK_BASE_BLOCKWITHLOCATORS
#define NJOY_ACETK_BASE_BLOCKWITHLOCATORS

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief The base class for a combined locator and data block like the
 *         LSIG&SIG, LDLW&DLW, etc. blocks
 */
template < typename Derived, typename Data >
class BlockWithLocators : protected Base {

  /* fields */

  unsigned int n_;           // the number of data blocks
  bool locator_;             // flag to indicate if locators or offsets are used
  Iterator iterator_;        // the begin iterator of the data block
  std::vector< Data > data_; // the data blocks

  /* auxiliary functions */

  static std::vector< double > generateXSS( std::vector< Data >&& blocks,
                                            bool locator ) {

    const auto n = blocks.size();
    std::vector< double > xss( n );
    std::size_t index = 0;
    for ( const auto& data : blocks ) {

      xss[index] = static_cast< double >( locator ? xss.size() - n + 1
                                                  : xss.size() - n );
      xss.insert( xss.end(), data.begin(), data.end() );
      ++index;
    }

    return xss;
  }

  // The Derived class can override this function to generate a data block (like
  // a cross section data block from the SIG block) that cannot use the basic
  // constructor of a left an right iterator (e.g. when the data block is a
  // variant).
  static Data generateData( std::size_t locator, Iterator left, Iterator right ) {

    if ( locator == 0 ) {

      Log::warning( "Detected a locator = 0 that may not be properly handled" );
    }

    return { left, right };
  }

  // The generateData function can be overriden in the Derived class to handle
  // more complex cases involving variants. If overriding the generateData
  // function does not handle the entire situation, overriding the generateBlocks
  // directly is also possible.
  void generateBlocks() {

    this->data_.clear();

    for ( unsigned int index = 1; index <= this->N(); ++index ) {

      // data : one-based index to the start of the data block
      // data + locator - 1 : one-based index to the start of cross section data
      std::size_t data = std::distance( this->begin(), this->iter() ) + 1;
      std::size_t locator = this->LLOC( index );
      const auto left = this->iterator( data + locator - 1 );
      const auto right = index == this->N()
                         ? this->end()
                         : this->iterator( data + this->LLOC( index + 1 ) - 1 );
      this->data_.emplace_back( Derived::generateData( locator, left, right ) );
    }
  }

  void verifySize( Iterator begin, Iterator data, Iterator,
                   unsigned int n ) {

    // there are at least n values in the locator block
    auto size = std::distance( begin, data );
    if ( size < n ) {

      Log::error( "The size of the XSS subrange in the locator part of the {} "
                  "block should be at least N", this->name() );
      Log::info( "N value: {}", n );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  BlockWithLocators( std::string&& name, std::vector< Data >&& xs,
                     std::size_t n, bool locator ) :
    Base( std::move( name ), Derived::generateXSS( std::move( xs ), locator ) ),
    n_( n ), locator_( locator ) {

    this->iterator_ = this->begin() + this->N();
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

  BlockWithLocators() = default;

  BlockWithLocators( const BlockWithLocators& base ) :
    Base( base ), n_( base.n_ ), locator_( base.locator_ ),
    iterator_( base.iterator_ ), data_( base.data_ ) {

    if ( Base::owner() ) {

      this->iterator_ = this->begin() + this->N();
      static_cast< Derived* >( this )->generateBlocks();
    }
  }

  BlockWithLocators( BlockWithLocators&& base ) :
    Base( std::move( base ) ), n_( base.n_ ), locator_( base.locator_ ),
    iterator_( base.iterator_ ), data_( std::move( base.data_ ) ) {

    if ( Base::owner() ) {

      this->iterator_ = this->begin() + this->N();
      static_cast< Derived* >( this )->generateBlocks();
    }
  }

  /**
   *  @brief Constructor for a block
   *
   *  @param[in] name       the block name
   *  @param[in] data       the data
   *  @param[in] locator    flag to indicate if the L values are to be interpreted
   *                        as locators or offsets
   */
  BlockWithLocators( std::string name, std::vector< Data > data, bool locator = true ) :
    BlockWithLocators( std::move( name ), std::move( data ), data.size(), locator ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] name       the block name
   *  @param[in] loc        the begin iterator of the LSIG block in the XSS array
   *  @param[in] data       the begin iterator of the SIG block in the XSS array
   *  @param[in] end        the end iterator of the SIG block in the XSS array
   *  @param[in] n          the number of reactions (excluding elastic)
   *  @param[in] locator    flag to indicate if the L values are to be interpreted
   *                        as locators or offsets
   */
  BlockWithLocators( std::string name,
                     Iterator loc, Iterator data, Iterator end,
                     unsigned int n, bool locator = true ) :
    Base( std::move( name ), loc, end ),
    n_( n ), locator_( locator ), iterator_( data ) {

    verifySize( this->begin(), this->iterator_, this->end(), this->N() );
    static_cast< Derived* >( this )->generateBlocks();
  }

  BlockWithLocators& operator=( const BlockWithLocators& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->n_ = base.n_;
      this->locator_ = base.locator_;
      this->iterator_ = base.iterator_;
      this->data_ = base.data_;
      if ( Base::owner() ) {

        this->iterator_ = this->begin() + this->N();
        static_cast< Derived* >( this )->generateBlocks();
      }
    }
    return *this;
  }

  BlockWithLocators& operator=( BlockWithLocators&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->n_ = base.n_;
      this->locator_ = base.locator_;
      this->iterator_ = base.iterator_;
      this->data_ = std::move( base.data_ );
      if ( Base::owner() ) {

        this->iterator_ = this->begin() + this->N();
        static_cast< Derived* >( this )->generateBlocks();
      }
    }
    return *this;
  }

  /**
   *  @brief Return the iterator to the start of the data block
   */
  Iterator iter() const { return this->iterator_; }

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
    return this->locator_ ? this->IXSS( index ) : this->IXSS( index ) + 1;
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
   *  @brief Return the data vector
   */
  const std::vector< Data >& data() const {

    return this->data_;
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
