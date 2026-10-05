#ifndef NJOY_ACETK_CONTINUOUS_DELAYEDNEUTRONPRECURSORBLOCK
#define NJOY_ACETK_CONTINUOUS_DELAYEDNEUTRONPRECURSORBLOCK

// system includes

// other includes
#include "ACEtk/continuous/DelayedNeutronPrecursorData.hpp"
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy BDD block with the delayed neutron precursor
 *         data
 *
 *  The number of precursor groups is stored in NXS(8).
 */
class DelayedNeutronPrecursorBlock : protected base::Base {

  /* fields */

  unsigned int npcr_ = 0;
  std::vector< DelayedNeutronPrecursorData > data_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( std::vector< DelayedNeutronPrecursorData >&& groups ) {

    std::vector< double > xss;
    // commmenting this out for now - potential clash with user provided data
    // std::sort( groups.begin(), groups.end(),
    //            [] ( auto&& left, auto&& right )
    //               { return left.number() < right.number(); } );
    for ( const auto& group : groups ) {

      xss.insert( xss.end(), group.begin(), group.end() );
    }
    return xss;
  }

  void generateBlocks() {

      this->data_.clear();

    auto begin = this->begin();
    auto left = begin;
    auto right = begin;
    std::size_t locator = 1;
    for ( unsigned int index = 1; index <= this->NPCR(); ++index ) {

      std::size_t nr = static_cast< std::size_t >( this->IXSS( locator + 1 ) );
      std::size_t ne = static_cast< std::size_t >( this->IXSS( locator + 1 + 2 * nr + 1 ) );
      locator += 2 + 2 * nr + 2 * ne + 1;
      right = begin + ( locator - 1 );
      this->data_.emplace_back( left, right, index );
      left = right;
    }
  }

  void verifyGroupIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->NPCR() ) ) {

      Log::error( "Illegal index argument into the {} block", this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between 1 and {} inclusively",
                 this->name(), this->NPCR() );
      throw std::out_of_range( this->name() );
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  DelayedNeutronPrecursorBlock( std::vector< DelayedNeutronPrecursorData >&& groups,
                                std::size_t npcr ) :
    Base( "BDD", generateXSS( std::move( groups ) ) ),
    npcr_( npcr ) {

    this->generateBlocks();
  }

public:

  /* constructor */

  DelayedNeutronPrecursorBlock() = default;

  DelayedNeutronPrecursorBlock( const DelayedNeutronPrecursorBlock& base ) :
    Base( base ), npcr_( base.npcr_ ),
    data_( base.data_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  DelayedNeutronPrecursorBlock( DelayedNeutronPrecursorBlock&& base ) :
    Base( std::move( base ) ), npcr_( base.npcr_ ),
    data_( std::move( base.data_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  DelayedNeutronPrecursorBlock& operator=( const DelayedNeutronPrecursorBlock& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->npcr_ = base.npcr_;
      this->data_ = base.data_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  DelayedNeutronPrecursorBlock& operator=( DelayedNeutronPrecursorBlock&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->npcr_ = base.npcr_;
      this->data_ = std::move( base.data_ );
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] groups    the data for the precursor groups
   */
  DelayedNeutronPrecursorBlock( std::vector< DelayedNeutronPrecursorData > groups ) :
    DelayedNeutronPrecursorBlock( std::move( groups ), groups.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] bdd    the begin iterator of the BDD block in the XSS array
   *  @param[in] end    the end iterator of the BDD block in the XSS array
   *  @param[in] npcr   the number of delayed precursor groups
   */
  DelayedNeutronPrecursorBlock( Iterator bdd, Iterator end, unsigned int npcr ) :
    Base( "BDD", bdd, end ), npcr_( npcr ) {

    this->generateBlocks();
  }

  /* methods */

  /**
   *  @brief Return the number of delayed neutron precursor groups
   */
  unsigned int NPCR() const { return this->npcr_; }

  /**
   *  @brief Return the number of delayed neutron precursor groups
   */
  unsigned int numberDelayedPrecursors() const {

    return this->NPCR();
  }

  /**
   *  @brief Return the precursor data
   */
  const std::vector< DelayedNeutronPrecursorData >& data() const {

    return this->data_;
  }

  /**
   *  @brief Return the precursor group data for a precursor group index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DelayedNeutronPrecursorData& precursorGroupData( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyGroupIndex( index );
    #endif
    return this->data_[ index - 1 ];
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using BDD = DelayedNeutronPrecursorBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
