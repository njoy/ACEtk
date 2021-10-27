#ifndef NJOY_ACETK_BLOCK_DETAILS_DISTRIBUTIONDATABASE
#define NJOY_ACETK_BLOCK_DETAILS_DISTRIBUTIONDATABASE

// system includes
#include <variant>

// other includes
#include "utility/overload.hpp"
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/details/ColumnData.hpp"
#include "ACEtk/block/InterpolationData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief Base class for distribution data as a function of incident energy
 */
template< typename Distribution >
class BaseDistributionData : protected details::Base {

  /* fields */
  std::size_t locb_;
  InterpolationData interpolation_;
  details::ColumnData data_;

  /* auxiliary functions */
  #include "ACEtk/block/details/BaseDistributionData/src/generateXSS.hpp"
  #include "ACEtk/block/details/BaseDistributionData/src/verifyIncidentEnergyIndex.hpp"
  #include "ACEtk/block/details/BaseDistributionData/src/generateBlocks.hpp"
  #include "ACEtk/block/details/BaseDistributionData/src/verifySize.hpp"

protected:

  /* constructor */
  #include "ACEtk/block/details/BaseDistributionData/src/ctor.hpp"

public:

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
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return this->data_.N(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->data_.column( 1 ); }

  /**
   *  @brief Return the incident energy for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double incidentEnergy( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->data_.value( 1, index );
  }

  /**
   *  @brief Return the angular distribution locator for an incident
   *         energy index
   *
   *  This locator is the value as stored in the XSS array.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LOCC( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->data_.value( 2, index );
  }

  /**
   *  @brief Return the angular distribution locator for an incident
   *         energy index
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
   *  @brief Return the relative angular distribution locator for an incident
   *         energy index
   *
   *  This is the locator relative to the beginning of the current distribution
   *  block.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t relativeDistributionLocator( std::size_t index ) const {

    const int locator = this->LOCC( index );
    return locator - this->locb_ + 1;
  }

  /**
   *  @brief Return the distribution for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  Distribution distribution( std::size_t index ) const {

    const double incident = this->incidentEnergy( index );
    const auto locator = this->relativeDistributionLocator( index );
    const auto left = std::next( this->begin(), locator - 1 );
    const auto right = index == this->numberIncidentEnergies()
                       ? this->end()
                       : std::next( this->begin(),
                         this->relativeDistributionLocator( index + 1 ) - 1 );
    return Distribution( incident, left, right );
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
