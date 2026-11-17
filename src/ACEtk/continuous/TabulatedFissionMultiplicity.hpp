#ifndef NJOY_ACETK_CONTINUOUS_TABULATEDFISSIONMULTIPLICITY
#define NJOY_ACETK_CONTINUOUS_TABULATEDFISSIONMULTIPLICITY

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Tabulated fission multiplicity
 *
 *  The TabulatedFissionMultiplicity class contains the tabulated
 *  representation (LNU = 2) of the fission multiplicity. It is
 *  used in the NU block.
 */
class TabulatedFissionMultiplicity : protected base::Base {

  /* fields */

  base::TabulatedData data_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( std::vector< long >&& boundaries,
               std::vector< long >&& interpolants,
               std::vector< double >&& x,
               std::vector< double >&& y ) {

    std::vector< double > xss = { 2. };
    const base::TabulatedData data( "TabulatedFissionMultiplicity",
                                    std::move( boundaries ),
                                    std::move( interpolants ),
                                    std::move( x ),
                                    std::move( y ) );
    xss.insert( xss.end(), data.begin(), data.end() );
    return xss;
  }

  void generateBlocks() {

    this->data_ = base::TabulatedData( this->name(), this->begin() + 1, this->end() );
  }

public:

  /* constructor */

  TabulatedFissionMultiplicity() = default;

  TabulatedFissionMultiplicity( const TabulatedFissionMultiplicity& base ) :
    Base( base ), data_( base.data_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  TabulatedFissionMultiplicity( TabulatedFissionMultiplicity&& base ) :
    Base( std::move( base ) ), data_( std::move( base.data_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  TabulatedFissionMultiplicity& operator=( const TabulatedFissionMultiplicity& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->data_ = base.data_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  TabulatedFissionMultiplicity& operator=( TabulatedFissionMultiplicity&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
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
   *  @param[in] boundaries        the interpolation range boundaries
   *  @param[in] interpolants      the interpolation types for each range
   *  @param[in] energies          the energy values
   *  @param[in] multiplicities    the multiplicity values
   */
  TabulatedFissionMultiplicity( std::vector< long > boundaries,
                                std::vector< long > interpolants,
                                std::vector< double > energies,
                                std::vector< double > multiplicities ) :
    Base( "TabulatedFissionMultiplicity",
          generateXSS( std::move( boundaries ), std::move( interpolants ),
                       std::move( energies ), std::move( multiplicities ) ) ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] energies          the energy values
   *  @param[in] multiplicities    the multiplicity values
   */
  TabulatedFissionMultiplicity( std::vector< double > energies,
                                std::vector< double > multiplicities ) :
   TabulatedFissionMultiplicity( {}, {}, std::move( energies ),
                                 std::move( multiplicities ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the multiplicity data in the XSS array
   *  @param[in] end      the end iterator of the multiplicity data in the XSS array
   */
  TabulatedFissionMultiplicity( Iterator begin, Iterator end ) :
    Base( "TabulatedFissionMultiplicity", begin, end ) {

    this->generateBlocks();
  }

  /**
   *  @brief Return the representation type (should always be 2)
   */
  unsigned int LNU() const {

    return static_cast< unsigned int >( this->IXSS( 1 ) );
  }

  /**
   *  @brief Return the representation type (should always be 2)
   */
  std::size_t type() const { return this->LNU(); }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const { return this->data_.interpolationData(); }

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
   *  @brief Return the number of values
   */
  std::size_t NE() const { return this->data_.N(); }

  /**
   *  @brief Return the number of values
   */
  std::size_t numberValues() const { return this->NE(); }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return this->data_.x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the multiplicities
   */
  auto NU() const { return this->data_.y(); }

  /**
   *  @brief Return the multiplicities
   */
  auto multiplicities() const { return this->NU(); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
