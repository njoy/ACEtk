#ifndef NJOY_ACETK_ELECTROATOMIC_TABULATEDANGULARDISTRIBUTION
#define NJOY_ACETK_ELECTROATOMIC_TABULATEDANGULARDISTRIBUTION

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

/**
 *  @class
 *  @brief Tabulated electron angular distribution data for a single incident
 *         energy
 *
 *  The TabulatedAngularDistribution class contains the cumulative
 *  density function (CDF) as a function of cosine for the given incident
 *  energy. It is used in the ELAS block.
 */
class TabulatedAngularDistribution : protected base::ArrayData {

  /* fields */

  double energy_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */

  TabulatedAngularDistribution() = default;

  TabulatedAngularDistribution( const TabulatedAngularDistribution& ) = default;
  TabulatedAngularDistribution( TabulatedAngularDistribution&& ) = default;

  TabulatedAngularDistribution& operator=( const TabulatedAngularDistribution& ) = default;
  TabulatedAngularDistribution& operator=( TabulatedAngularDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energy          the associated energy value
   *  @param[in] cosines         the cosine values (LA values)
   *  @param[in] cdf             the cdf values (LA values)
   */
  TabulatedAngularDistribution( double energy,
                                std::vector< double > cosines,
                                std::vector< double > cdf ) :
    ArrayData( "TabulatedAngularDistribution",
               std::move( cosines ), std::move( cdf ) ),
    energy_( energy ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] energy    the associated energy value
   *  @param[in] begin     the begin iterator of the tabulated distribution data
   *  @param[in] end       the end iterator of the tabulated distribution data
   *  @param[in] la        the number of cosine values
   */
  TabulatedAngularDistribution( double energy,
                                Iterator begin, Iterator end,
                                unsigned int la ) :
    ArrayData( "TabulatedAngularDistribution", begin, end, la, 2 ),
    energy_( energy ) {}

  /**
   *  @brief Return the associated incident energy value
   */
  double energy() const { return this->energy_; }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t L() const { return this->N(); }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t LA() const { return this->L(); }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t numberCosines() const { return this->LA(); }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const { return this->darray( 1 ); }

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
