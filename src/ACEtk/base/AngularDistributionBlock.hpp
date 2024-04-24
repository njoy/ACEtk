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
  #include "ACEtk/base/AngularDistributionBlock/src/insertZero.hpp"
  #include "ACEtk/base/AngularDistributionBlock/src/generateXSS.hpp"
  #include "ACEtk/base/AngularDistributionBlock/src/generateBlocks.hpp"
  #include "ACEtk/base/AngularDistributionBlock/src/verifySize.hpp"
  #include "ACEtk/base/AngularDistributionBlock/src/verifyDataIndex.hpp"

public:

  /* constructor */
  #include "ACEtk/base/AngularDistributionBlock/src/ctor.hpp"

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
