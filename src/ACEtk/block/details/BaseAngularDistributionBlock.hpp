#ifndef NJOY_ACETK_BLOCK_DETAILS_BASEANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_DETAILS_BASEANGULARDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/AngularDistributionData.hpp"
#include "ACEtk/block/FullyIsotropicDistribution.hpp"
#include "ACEtk/block/DistributionGivenElsewhere.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief Base class for angular distribution data, capable of accepting both a
 *         zero or one based reaction index
 */
class BaseAngularDistributionBlock : protected details::Base {

public:

  /* type alias */
  using DistributionData = std::variant< FullyIsotropicDistribution,
                                         DistributionGivenElsewhere,
                                         AngularDistributionData >;

private:

  /* fields */
  unsigned int nr_;   // number of available reactions (excluding the zero index)
  Iterator iterator_; // the begin iterator of the actual data block
  std::vector< DistributionData > data_;
  bool zero_index_;

  /* auxiliary functions */
  #include "ACEtk/block/details/BaseAngularDistributionBlock/src/insertZero.hpp"
  #include "ACEtk/block/details/BaseAngularDistributionBlock/src/generateXSS.hpp"
  #include "ACEtk/block/details/BaseAngularDistributionBlock/src/generateBlocks.hpp"
  #include "ACEtk/block/details/BaseAngularDistributionBlock/src/verifySize.hpp"
  #include "ACEtk/block/details/BaseAngularDistributionBlock/src/verifyDataIndex.hpp"

public:

  /* constructor */
  #include "ACEtk/block/details/BaseAngularDistributionBlock/src/ctor.hpp"

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
    return XSS( index + offset ); // elastic is index 0
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
  using Base::begin;
  using Base::end;
};

} // details namespace
} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif