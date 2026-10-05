#ifndef NJOY_ACETK_CONTINUOUS_TABULATEDSECONDARYPARTICLEMULTIPLICITY
#define NJOY_ACETK_CONTINUOUS_TABULATEDSECONDARYPARTICLEMULTIPLICITY

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Tabulated secondary particle multiplicity
 *
 *  The TabulatedSecondaryParticleMultiplicity class contains tabulated
 *  multiplicities for a secondary particle (MFMULT = 12 or 16). It also
 *  contains the MT number of the associated reaction.
 */
class TabulatedSecondaryParticleMultiplicity : protected base::Base {

  /* fields */

  base::TabulatedData data_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( unsigned int mftype, unsigned int mt,
               std::vector< long >&& boundaries,
               std::vector< long >&& interpolants,
               std::vector< double >&& x,
               std::vector< double >&& y ) {

    std::vector< double > xss = { static_cast< double >( mftype ),
                                  static_cast< double >( mt ) };
    base::TabulatedData data( "TabulatedSecondaryParticleMultiplicity",
                              std::move( boundaries ),
                              std::move( interpolants ),
                              std::move( x ),
                              std::move( y ) );
    xss.insert( xss.end(), data.begin(), data.end() );
    return xss;
  }

  void generateBlocks() {

    this->data_ = base::TabulatedData( this->name(), this->begin() + 2, this->end() );
  }

public:

  /* constructor */

  TabulatedSecondaryParticleMultiplicity() = default;

  TabulatedSecondaryParticleMultiplicity( const TabulatedSecondaryParticleMultiplicity& base ) :
    Base( base ), data_( base.data_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  TabulatedSecondaryParticleMultiplicity( TabulatedSecondaryParticleMultiplicity&& base ) :
    Base( std::move( base ) ), data_( std::move( base.data_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  TabulatedSecondaryParticleMultiplicity& operator=( const TabulatedSecondaryParticleMultiplicity& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->data_ = base.data_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  TabulatedSecondaryParticleMultiplicity& operator=( TabulatedSecondaryParticleMultiplicity&& base ) {

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
   *  @param[in] mftype            the type (12 or 16)
   *  @param[in] mt                the associated reaction number
   *  @param[in] boundaries        the interpolation range boundaries
   *  @param[in] interpolants      the interpolation types for each range
   *  @param[in] energies          the energy values
   *  @param[in] multiplicities    the multiplicity values
   */
  TabulatedSecondaryParticleMultiplicity( unsigned int mftype, unsigned int mt,
                                          std::vector< long > boundaries,
                                          std::vector< long > interpolants,
                                          std::vector< double > energies,
                                          std::vector< double > multiplicities ) :
    Base( "TabulatedSecondaryParticleMultiplicity",
          generateXSS( mftype, mt,
                       std::move( boundaries ), std::move( interpolants ),
                       std::move( energies ), std::move( multiplicities ) ) ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] mfmult            the type (12 or 16)
   *  @param[in] mt                the associated reaction number
   *  @param[in] energies          the energy values
   *  @param[in] multiplicities    the multiplicity values
   */
  TabulatedSecondaryParticleMultiplicity( unsigned int mftype, unsigned int mt,
                                          std::vector< double > energies,
                                          std::vector< double > multiplicities ) :
   TabulatedSecondaryParticleMultiplicity( mftype, mt, {}, {},
                                           std::move( energies ),
                                           std::move( multiplicities ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the multiplicity data in the XSS array
   *  @param[in] end      the end iterator of the multiplicity data in the XSS array
   */
  TabulatedSecondaryParticleMultiplicity( Iterator begin, Iterator end ) :
    Base( "TabulatedSecondaryParticleMultiplicity", begin, end ) {

    this->generateBlocks();
  }

  /**
   *  @brief Return the representation type (should always be 12 or 16)
   */
  unsigned int MFTYPE() const {

    return static_cast< unsigned int >( this->IXSS( 1 ) );
  }

  /**
   *  @brief Return the representation type (should always be 12 or 16)
   */
  unsigned int type() const { return this->MFTYPE(); }

  /**
   *  @brief Return the associated reaction number
   */
  unsigned int MT() const {

    return static_cast< unsigned int >( this->IXSS( 2 ) );
  }

  /**
   *  @brief Return the associated reaction number
   */
  unsigned int reactionNumber() const { return this->MT(); }

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
