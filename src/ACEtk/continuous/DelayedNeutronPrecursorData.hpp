#ifndef NJOY_ACETK_CONTINUOUS_DELAYEDNEUTRONPRECURSORDATA
#define NJOY_ACETK_CONTINUOUS_DELAYEDNEUTRONPRECURSORDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Delayed neutron precursor group data
 *
 *  The DelayedNeutronPrecursorData class contains the prrcursor group's decay
 *  constant and the associated probability as a function of incident energy.
 */
class DelayedNeutronPrecursorData : protected base::Base {

  /* fields */

  unsigned int number_ = 0;
  base::TabulatedData data_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( double lambda,
               std::vector< long >&& boundaries,
               std::vector< long >&& interpolants,
               std::vector< double >&& x,
               std::vector< double >&& y ) {

    std::vector< double > xss = { lambda };
    const base::TabulatedData data( "DelayedNeutronPrecursorData",
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

  DelayedNeutronPrecursorData() = default;

  DelayedNeutronPrecursorData( const DelayedNeutronPrecursorData& base ) :
    Base( base ), number_( base.number_ ),
    data_( base.data_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  DelayedNeutronPrecursorData( DelayedNeutronPrecursorData&& base ) :
    Base( std::move( base ) ), number_( base.number_ ),
    data_( std::move( base.data_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  DelayedNeutronPrecursorData& operator=( const DelayedNeutronPrecursorData& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->number_ = base.number_;
      this->data_ = base.data_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  DelayedNeutronPrecursorData& operator=( DelayedNeutronPrecursorData&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->number_ = base.number_;
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
   *  @param[in] number            the precursor group number
   *  @param[in] constant          the precursor group's decay constant
   *  @param[in] boundaries        the interpolation range boundaries
   *  @param[in] interpolants      the interpolation types for each range
   *  @param[in] energies          the energy values
   *  @param[in] multiplicities    the multiplicity values
   */
  DelayedNeutronPrecursorData( unsigned int number, double constant,
                               std::vector< long > boundaries,
                               std::vector< long > interpolants,
                               std::vector< double > energies,
                               std::vector< double > multiplicities ) :
    Base( "DelayedNeutronPrecursorData",
          generateXSS( constant,
                       std::move( boundaries ), std::move( interpolants ),
                       std::move( energies ), std::move( multiplicities ) ) ),
    number_( number ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] number            the precursor group number
   *  @param[in] constant          the precursor group's decay constant
   *  @param[in] energies          the energy values
   *  @param[in] multiplicities    the multiplicity values
   */
  DelayedNeutronPrecursorData( unsigned int number, double constant,
                               std::vector< double > energies,
                               std::vector< double > multiplicities ) :
   DelayedNeutronPrecursorData( number, constant, {}, {}, std::move( energies ),
                                std::move( multiplicities ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] number   the precursor group number
   *  @param[in] begin    the begin iterator of the multiplicity data in the XSS array
   *  @param[in] end      the end iterator of the multiplicity data in the XSS array
   */
  DelayedNeutronPrecursorData( Iterator begin, Iterator end, unsigned int number ) :
    Base( "DelayedNeutronPrecursorData", begin, end ),
    number_( number ) {

    this->generateBlocks();
  }

  /**
   *  @brief Return the delayed precursor group number
   */
  unsigned int number() const { return this->number_; }

  /**
   *  @brief Return the decay constant
   */
  double DEC() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the decay constant
   */
  double decayConstant() const { return this->DEC(); }

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
   *  @brief Return the probabilities
   */
  auto P() const { return this->data_.y(); }

  /**
   *  @brief Return the probabilities
   */
  auto probabilities() const { return this->P(); }

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
