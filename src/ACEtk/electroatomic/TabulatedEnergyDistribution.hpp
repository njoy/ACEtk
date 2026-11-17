#ifndef NJOY_ACETK_ELECTROATOMIC_TABULATEDENERGYDISTRIBUTION
#define NJOY_ACETK_ELECTROATOMIC_TABULATEDENERGYDISTRIBUTION

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

/**
 *  @class
 *  @brief Tabulated photon energy distribution from Bremsstrahlung for a single
 *         incident energy
 *
 *  The TabulatedEnergyDistribution class contains the cumulative density
 *  function (CDF) as a function of photon energy for the given incident
 *  energy. It is used in the BREME block.
 */
class TabulatedEnergyDistribution : protected base::ArrayData {

  /* fields */

  double energy_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */

  TabulatedEnergyDistribution() = default;

  TabulatedEnergyDistribution( const TabulatedEnergyDistribution& ) = default;
  TabulatedEnergyDistribution( TabulatedEnergyDistribution&& ) = default;

  TabulatedEnergyDistribution& operator=( const TabulatedEnergyDistribution& ) = default;
  TabulatedEnergyDistribution& operator=( TabulatedEnergyDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energy      the associated energy value
   *  @param[in] outgoing    the outgoing energy values (LB values)
   *  @param[in] cdf         the cdf values (LB values)
   */
  TabulatedEnergyDistribution( double energy,
                               std::vector< double > outgoing,
                               std::vector< double > cdf ) :
    ArrayData( "TabulatedEnergyDistribution",
               std::move( outgoing ), std::move( cdf ) ),
    energy_( energy ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] energy    the associated energy value
   *  @param[in] begin     the begin iterator of the tabulated distribution data
   *  @param[in] end       the end iterator of the tabulated distribution data
   *  @param[in] lb        the number of outgoing energy values
   */
  TabulatedEnergyDistribution( double energy,
                               Iterator begin, Iterator end,
                               unsigned int la ) :
    ArrayData( "TabulatedEnergyDistribution", begin, end, la, 2 ),
    energy_( energy ) {}

  /**
   *  @brief Return the associated incident energy value
   */
  double energy() const { return this->energy_; }

  /**
   *  @brief Return the number of outgoing energy values
   */
  std::size_t L() const { return this->N(); }

  /**
   *  @brief Return the number of outgoing energy values
   */
  std::size_t LB() const { return this->L(); }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t numberOutgoingEnergies() const { return this->LB(); }

  /**
   *  @brief Return the outgoing energy values
   */
  auto outgoingEnergies() const { return this->darray( 1 ); }

  /**
   *  @brief Return the cdf values
   */
  auto cdf() const { return this->darray( 2 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
