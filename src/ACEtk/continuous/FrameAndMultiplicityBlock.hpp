#ifndef NJOY_ACETK_CONTINUOUS_FRAMEANDMULTIPLICITYBLOCK
#define NJOY_ACETK_CONTINUOUS_FRAMEANDMULTIPLICITYBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/ReferenceFrame.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy TYR block with the outgoing projectile
 *         multiplicities and reference frames
 *
 *  The FrameAndMultiplicityBlock class contains the reference frame and
 *  outgoing projectile multiplicity. The order of this data is the same as
 *  the order of the reaction numbers in the MTR block.
 *
 *  The number of available reactions (excluding elastic) is stored in NXS(4).
 */
class FrameAndMultiplicityBlock : protected base::Base {

  /* fields */

  std::size_t ntr_ = 0;
  std::vector< ReferenceFrame > frames_;
  std::vector< unsigned int > multiplicities_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( std::vector< ReferenceFrame >&& frames,
               std::vector< unsigned int >&& multiplicities ) {

    std::vector< double > xss;
    const auto ntr = multiplicities.size();
    xss.reserve( ntr );

    if ( frames.size() != ntr ) {

      Log::error( "The size of the TYR subranges are not consistent" );
      Log::info( "NTR value: {}", ntr );
      Log::info( "frames.size(): {}", ntr );
      Log::info( "multiplicities.size(): {}", multiplicities.size() );
      throw std::exception();
    }

    xss.insert( xss.end(), multiplicities.begin(), multiplicities.end() );
    for ( unsigned int i = 0; i < ntr; ++i ) {

      if ( frames[i] == ReferenceFrame::CentreOfMass ) {

        xss[i] *= -1;
      }
    }

    return xss;
  }

  static std::vector< double >
  generateXSS( std::vector< ReferenceFrame >&& frames ) {

    std::vector< double > xss( frames.size(), 1 );
    for ( unsigned int i = 0; i < frames.size(); ++i ) {

      if ( frames[i] == ReferenceFrame::CentreOfMass ) {

        xss[i] = -1;
      }
    }
    return xss;
  }

  void generateBlocks() {

    this->frames_.clear();
    this->multiplicities_.clear();

    for ( std::size_t index = 1; index <= this->NTR(); ++index ) {

      this->frames_.emplace_back( this->XSS( index ) < 0
                                  ? ReferenceFrame::CentreOfMass
                                  : ReferenceFrame::Laboratory );
      this->multiplicities_.emplace_back(
                 static_cast< unsigned int >( std::abs( this->IXSS( index ) ) ) );
    }
  }

  static void verifySize( Iterator begin, Iterator end, unsigned int ntr ) {

    auto size = std::distance( begin, end );
    if ( size < ntr ) {

      Log::error( "The size of the XSS subrange should be at least NTR" );
      Log::info( "NTR value: {}", ntr );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  FrameAndMultiplicityBlock( std::vector< ReferenceFrame >&& frames,
                             std::vector< unsigned int >&& multiplicities,
                             std::size_t ntr ) :
    Base( "TYR", generateXSS( std::move( frames ), std::move( multiplicities ) ) ),
    ntr_( ntr ) {

    this->generateBlocks();
  }

  /**
   *  @brief Private constructor
   */
  FrameAndMultiplicityBlock( std::vector< ReferenceFrame >&& frames,
                             std::size_t ntr ) :
    Base( "TYR", generateXSS( std::move( frames ) ) ), ntr_( ntr ) {

    this->generateBlocks();
  }

public:

  /* constructor */

  FrameAndMultiplicityBlock() = default;

  FrameAndMultiplicityBlock( const FrameAndMultiplicityBlock& base ) :
    Base( base ), ntr_( base.ntr_ ),
    frames_( base.frames_ ),
    multiplicities_( base.multiplicities_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  FrameAndMultiplicityBlock( FrameAndMultiplicityBlock&& base ) :
    Base( std::move( base ) ), ntr_( base.ntr_ ),
    frames_( std::move( base.frames_ ) ),
    multiplicities_( std::move( base.multiplicities_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  FrameAndMultiplicityBlock& operator=( const FrameAndMultiplicityBlock& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->ntr_ = base.ntr_;
      this->frames_ = base.frames_;
      this->multiplicities_ = base.multiplicities_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  FrameAndMultiplicityBlock& operator=( FrameAndMultiplicityBlock&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->ntr_ = base.ntr_;
      this->frames_ = std::move( base.frames_ );
      this->multiplicities_ = std::move( base.multiplicities_ );
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] frames            the reference frames
   *  @param[in] multiplicities    the multiplicities
   */
  FrameAndMultiplicityBlock( std::vector< ReferenceFrame > frames,
                             std::vector< unsigned int > multiplicities ) :
    FrameAndMultiplicityBlock( std::move( frames ), std::move( multiplicities ),
                               frames.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] frames            the reference frames
   */
  FrameAndMultiplicityBlock( std::vector< ReferenceFrame > frames ) :
    FrameAndMultiplicityBlock( std::move( frames ), frames.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] mtr   the begin iterator of the TYR block in the XSS array
   *  @param[in] end   the end iterator of the TYR block in the XSS array
   *  @param[in] ntr   the number of reactions (excluding elastic)
   */
  FrameAndMultiplicityBlock( Iterator tyr, Iterator end, unsigned int ntr ) :
    Base( "TYR", tyr, end ), ntr_( ntr ) {

    verifySize( this->begin(), this->end(), this->ntr_ );
    this->generateBlocks();
  }

  /* methods */

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  std::size_t NTR() const { return this->ntr_; }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  std::size_t numberReactions() const { return this->NTR(); }

  /**
   *  @brief Return the reference frame for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  const ReferenceFrame& referenceFrame( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyReactionIndex( index, 1, this->NTR() );
    #endif
    return this->frames_[ index - 1 ];
  }

  /**
   *  @brief Return the reference frames
   */
  const std::vector< ReferenceFrame >& referenceFrames() const {

    return this->frames_;
  }

  /**
   *  @brief Return the multiplicity value for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int multiplicity( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyReactionIndex( index, 1, this->NTR() );
    #endif
    return this->multiplicities_[ index - 1 ];
  }

  /**
   *  @brief Return the multiplicities
   */
  const std::vector< unsigned int >& multiplicities() const {

    return this->multiplicities_;
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using TYR = FrameAndMultiplicityBlock;
using TYRH = FrameAndMultiplicityBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
