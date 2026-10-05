#ifndef NJOY_ACETK_CONTINUOUS_PARAMETERDATA
#define NJOY_ACETK_CONTINUOUS_PARAMETERDATA

// system includes

// other includes
#include "ACEtk/base/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Parameter data for a Watt spectrum
 */
class ParameterData : protected base::TabulatedData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  ParameterData() = default;

  ParameterData( const ParameterData& ) = default;
  ParameterData( ParameterData&& ) = default;

  ParameterData& operator=( const ParameterData& ) = default;
  ParameterData& operator=( ParameterData&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the energy values
   *  @param[in] values          the parameter values
   */
  ParameterData( std::vector< long > boundaries,
                 std::vector< long > interpolants,
                 std::vector< double > energies,
                 std::vector< double > values ) :
    TabulatedData( "ParameterData", std::move( boundaries ), std::move( interpolants ),
                   std::move( energies ), std::move( values ) ) {}

  /**
   *  @brief Constructor (linear interpolation is assumed)
   *
   *  @param[in] energies        the energy values
   *  @param[in] values          the parameter values
   */
  ParameterData( std::vector< double > energies,
                 std::vector< double > values ) :
    ParameterData( {}, {}, std::move( energies ), std::move( values ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the block in the XSS array
   *  @param[in] end      the end iterator of the block in the XSS array
   */
  ParameterData( Iterator begin, Iterator end ) :
    TabulatedData( "ParameterData", begin, end ) {}

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return TabulatedData::interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return TabulatedData::NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return TabulatedData::numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return TabulatedData::NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return TabulatedData::boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return TabulatedData::INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return TabulatedData::interpolants(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t NE() const { return TabulatedData::N(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t numberEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return TabulatedData::x(); }

  /**
   *  @brief Return the parameter values
   */
  auto values() const { return TabulatedData::y(); }

  using TabulatedData::empty;
  using TabulatedData::name;
  using TabulatedData::length;
  using TabulatedData::XSS;
  using TabulatedData::begin;
  using TabulatedData::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
