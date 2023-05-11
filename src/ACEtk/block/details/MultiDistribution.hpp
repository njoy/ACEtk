#ifndef NJOY_ACETK_BLOCK_MULTIDISTRIBUTIONDATA
#define NJOY_ACETK_BLOCK_MULTIDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/DistributionProbability.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief The distribution of two or more distribution with their own probability
 *
 *  The MultiDistribution class contains a set of distributions and
 *  associated probabilities to represent the particle's distribution data.
 *  This type of distribution is rarely used, and when it happens it is often
 *  used for higher chance fission spectra or data from MF5. The distribution is
 *  templated to allow us to take into account the most common occurences that
 *  we have seen in legacy ACE files.
 *
 *  This class is set up as a CRTP and the derived class need the following
 *  functions implemented to function:
 *    - LAW() that return the law number
 *    - a static readDistributionData( ... ) function to read a single instance
 *      of DistributionData
 *    - a static retrieveLAW( ... ) function that retrieves the law number from
 *      a single instance
 *    - a static insertXSS( ... ) function that inserts the xss array from a
 *      single instance of DistributionData into the MultiDistribution's xss array
 *
 */
template < typename Derived, typename DistributionData >
class MultiDistribution : protected details::Base {

  /* fields */
  std::size_t locb_ = 1;
  std::vector< DistributionProbability > probabilities_;
  std::vector< DistributionData > distributions_;

  /* auxiliary functions */
  #include "ACEtk/block/details/MultiDistribution/src/generateBlocks.hpp"
  #include "ACEtk/block/details/MultiDistribution/src/verifyDistributionIndex.hpp"
  #include "ACEtk/block/details/MultiDistribution/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/details/MultiDistribution/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  constexpr EnergyDistributionType type() const {

    return static_cast< const Derived* >( this )->LAW();
  }

  /**
   *  @brief Return the number of distributions
   */
  std::size_t numberDistributions() const {

    return this->distributions_.size();
  }

  /**
   *  @brief Return the probability for each distribution
   */
  const std::vector< DistributionProbability >& probabilities() const {

    return this->probabilities_;
  }

  /**
   *  @brief Return the probability data for a distribution index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DistributionProbability& probability( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDistributionIndex( index );
    #endif
    return this->probabilities_[ index - 1 ];
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< DistributionData >& distributions() const {

    return this->distributions_;
  }

  /**
   *  @brief Return the distribution data for a distribution index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DistributionData& distribution( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDistributionIndex( index );
    #endif
    return this->distributions_[ index - 1 ];
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
