#ifndef NJOY_ACETK_THERMAL_INELASTICANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_THERMAL_INELASTICANGULARDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/thermal/DiscreteCosines.hpp"
#include "ACEtk/thermal/DiscreteCosinesWithProbability.hpp"

namespace njoy {
namespace ACEtk {
namespace thermal {

/**
 *  @class
 *  @brief The angular distribution block for inelastic thermal scattering
 *
 *  The InelasticAngularDistributionBlock class contains the equiprobable set or
 *  a skewed distribution of discrete cosines, or a tabulated probability
 *  distribution.
 */
class InelasticAngularDistributionBlock : protected base::Base {

public:

  /* type alias */

  using AngularDistributionData = std::variant< DiscreteCosines,
                                                DiscreteCosinesWithProbability >;

private:

  /* fields */

  unsigned int ifeng_;
  std::size_t nc_;
  std::optional< std::size_t > nieb_;
  std::size_t ne_;
  std::size_t locb_;
  std::vector< std::vector< AngularDistributionData > > data_;

  /* auxiliary functions */

  void generateBlocks() {

    this->data_.clear();

    auto ne = this->NE();
    auto nc = this->NC();
    if ( this->IFENG() < 2 ) {

      auto current = this->begin();
      auto end = current;
      for ( unsigned int incident = 1; incident <= ne; ++incident ) {

        auto nieb = this->NIEB( incident );
        std::vector< AngularDistributionData > data;
        for ( unsigned int outgoing = 1; outgoing <= nieb; ++outgoing ) {

          end = current + nc + 1;
          data.emplace_back( DiscreteCosines( nc, current, end ) );
          current = end;
        }
        this->data_.emplace_back( std::move( data ) );
      }
    }
    else {

      auto locator = this->relativeDistributionLocator( 1 );
      auto current = this->iterator( locator );
      auto end = current;
      for ( unsigned int incident = 1; incident <= ne; ++incident ) {

        locator = this->relativeDistributionLocator( incident + 1 );
        auto nieb = this->NIEB( incident );
        auto next = incident == ne ? this->end() : this->iterator( locator );

        std::vector< AngularDistributionData > data;
        for ( unsigned int outgoing = 1; outgoing <= nieb; ++outgoing ) {

          end = outgoing == nieb ? next : current + nc + 3;
          data.emplace_back( DiscreteCosinesWithProbability( nc, current, end ) );
          current = end;
        }
        this->data_.emplace_back( std::move( data ) );
      }
    }
  }

  void verifyIndex( const std::size_t incident ) const {

    std::size_t max = this->NE();
    if ( ( incident < 1 ) || ( incident > max ) ) {

      Log::error( "Illegal incident energy index argument into the {} block", this->name() );
      Log::info( "Index value: {}", incident );
      Log::info( "{} accepts an index between 1 and {} inclusively",
                 this->name(), max );
      throw std::out_of_range( this->name() );
    }
  }

  void verifyIndices( const std::size_t incident, const std::size_t outgoing ) const {

    this->verifyIndex( incident );

    std::size_t max = this->NIEB( incident );
    if ( ( outgoing < 1 ) || ( outgoing > max ) ) {

      Log::error( "Illegal outgoing energy index argument into the {} block", this->name() );
      Log::info( "Index value: {}", outgoing );
      Log::info( "{} accepts an index between 1 and {} inclusively",
                 this->name(), max );
      throw std::out_of_range( this->name() );
    }
  }

  void verifySize( Iterator begin, Iterator end, unsigned int ne,
                   unsigned int nieb, unsigned int nc ) {

    // there are at least nr values in the locator block
    auto size = std::distance( begin, end );
    if ( size < ne * nieb * ( 1 + nc ) ) {

      Log::error( "The size of the XSS array in the {} "
                  "block should be at least NE * NIEB * ( 1 + NC )", this->name() );
      Log::info( "NE value: {}", ne );
      Log::info( "NIEB value: {}", nieb );
      Log::info( "NC value: {}", nc );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateXSS(
    std::vector< std::vector< DiscreteCosines > >&& cosines,
    std::size_t ) {

    std::vector< double > xss;
    const auto ne = cosines.size();
    const auto nieb = cosines.front().size();
    for ( unsigned int i = 0; i < ne; ++i ) {

      if ( nieb != cosines[i].size() ) {

        Log::error( "The number of outgoing energies for the incident energy "
                    "with index {} is not equal to the expected number"
                    "expected value", i + 1 );
        Log::info( "Expected number = {}", nieb );
        Log::info( "Found number = {}", cosines[i].size() );
        throw std::exception();
      }

      for ( unsigned int j = 0; j < nieb; ++j ) {

        xss.insert( xss.end(), cosines[i][j].begin(), cosines[i][j].end() );
      }
    }

    return xss;
  }

  static std::vector< double >
  generateXSS(
    std::vector< std::vector< DiscreteCosinesWithProbability > >&& cosines,
    std::size_t locb ) {

    const auto size = cosines.size();
    std::vector< double > xss( size * 2 );
    std::size_t index = 0;
    for ( auto&& data : cosines ) {

      // current value of a locator into the xss array
      // these locators are the actual one-based indices into the xss array
      // so we need to know the size of the xss array prior to this being created
      std::size_t locator = xss.size() + 1;

      // set the locator and number of outgoing energies for the current incident
      // energy
      // Note: historically, these locators are off by 1
      xss[index] = static_cast< double >( locator + ( locb - 1 ) - 1 );
      xss[size + index] = static_cast< double >( data.size() );

      // insert every set of discrete cosines
      for ( auto&& entry : data ) {

        xss.insert( xss.end(), entry.begin(), entry.end() );
      }

      ++index;
    }

    return xss;
  }

  /**
   *  @brief Return the distribution locator for an incident energy index
   *
   *  This locator is the value as stored in the XSS array.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LOCC( std::size_t index ) const {

    return this->IXSS( index ) + 1;
  }

  /**
   *  @brief Return the distribution locator for an incident energy index
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
   *  @brief Return the relative distribution locator for a value index
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
    return locator - ( this->locb_ - 1 );
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template < typename Data >
  InelasticAngularDistributionBlock(
      std::vector< std::vector< Data > >&& cosines,
      unsigned int ifeng,
      unsigned int nc,
      std::optional< unsigned int > nieb,
      unsigned int ne,
      std::size_t locb ) :
    Base( "InelasticAngularDistributionBlock",
          generateXSS( std::move( cosines ), locb ) ),
    ifeng_( ifeng ), nc_( nc ), nieb_( nieb ), ne_( ne ), locb_( locb ) {

    this->generateBlocks();
  }

public:

  /* constructor */

  InelasticAngularDistributionBlock() = default;

  InelasticAngularDistributionBlock( const InelasticAngularDistributionBlock& base ) :
    Base( base ), ifeng_( base.ifeng_ ),
    nc_( base.nc_ ), nieb_( base.nieb_ ), ne_( base.ne_ ),
    locb_( base.locb_ ), data_( base.data_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  InelasticAngularDistributionBlock( InelasticAngularDistributionBlock&& base ) :
    Base( std::move( base ) ), ifeng_( base.ifeng_ ),
    nc_( base.nc_ ), nieb_( base.nieb_ ), ne_( base.ne_ ),
    locb_( base.locb_ ), data_( std::move( base.data_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  InelasticAngularDistributionBlock&
  operator=( const InelasticAngularDistributionBlock& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->ifeng_ = base.ifeng_;
      this->nc_ = base.nc_;
      this->nieb_ = base.nieb_;
      this->ne_ = base.ne_;
      this->locb_ = base.locb_;
      this->data_ = base.data_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  InelasticAngularDistributionBlock&
  operator=( InelasticAngularDistributionBlock&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->ifeng_ = base.ifeng_;
      this->nc_ = base.nc_;
      this->nieb_ = std::move( base.nieb_ );
      this->ne_ = base.ne_;
      this->locb_ = base.locb_;
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
   *  @param[in] cosines    the discrete cosine data for each incident and outgoing
   *                        energy value
   *  @param[in] skewed     flag to indicate whether or not the distribution is
   *                        skewed or equiprobable
   *  @param[in] locb       the starting xss index for the ITXE block (default = 1)
   */
  InelasticAngularDistributionBlock(
      std::vector< std::vector< DiscreteCosines > > cosines,
      bool skewed, std::size_t locb = 1 ) :
    InelasticAngularDistributionBlock(
        std::move( cosines ),
        static_cast< unsigned int >( skewed ),
        cosines.front().front().NC(),
        cosines.front().size(),
        cosines.size(),
        locb ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] cosines    the discrete cosine data for each incident and outgoing
   *                        energy value
   *  @param[in] locb       the starting xss index for the ITXE block (default = 1)
   */
  InelasticAngularDistributionBlock(
      std::vector< std::vector< DiscreteCosinesWithProbability > > cosines,
      std::size_t locb = 1 ) :
    InelasticAngularDistributionBlock(
        std::move( cosines ), 2, cosines.front().front().NC(),
        std::nullopt, cosines.size(), locb ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] ifeng      the inelastic format flag
   *  @param[in] nieb       the number of outgoing energy values (for ifeng < 2 only)
   *  @param[in] nc         the number of discrete cosine values
   *  @param[in] begin      the begin iterator of the angular distribution data
   *  @param[in] end        the end iterator of the angular distribution data
   */
  InelasticAngularDistributionBlock(
      unsigned int ifeng, std::size_t nieb, std::size_t nc, std::size_t ne,
      std::size_t locb, Iterator begin, Iterator end ) :
    Base( "InelasticAngularDistributionBlock", begin, end ),
    ifeng_( ifeng ), nc_( nc ),
    nieb_( ifeng < 2 ? std::optional< std::size_t >( nieb ) : std::nullopt ),
    ne_( ne ),locb_( locb ) {

    if ( ifeng < 2 ) {

      this->verifySize( this->begin(), this->end(), this->NE(),
                        this->nieb_.value(), this->NC() );
    }
    this->generateBlocks();
  }

  /**
   *  @brief Return the secondary energy mode
   */
  unsigned int IFENG() const { return this->ifeng_; }

  /**
   *  @brief Return the secondary energy mode
   */
  unsigned int secondaryEnergyMode() const { return this->IFENG(); }

  /**
   *  @brief Return the number of equiprobable discrete cosine values for each
   *         incident and outgoing energy pair
   */
  std::size_t NC() const { return this->nc_; }

  /**
   *  @brief Return the number of equiprobable discrete cosine values for each
   *         incident and outgoing energy pair
   */
  std::size_t numberDiscreteCosines() const { return this->NC(); }

  /**
   *  @brief Return the inelastic dimensioning parameter
   *
   *  For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,
   *  for IFENG = 2 this will be equal to NC + 1
   */
  std::size_t NIL() const { return this->IFENG() < 2 ? this->NC() - 1
                                                     : this->NC() + 1; }

  /**
   *  @brief Return the inelastic dimensioning parameter
   *
   *  For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,
   *  for IFENG = 2 this will be equal to NC + 1
   */
  std::size_t inelasticDimensioningParameter() const { return this->NIL(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return this->ne_; }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the number of secondary energies for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t NIEB( std::size_t index ) const {

    if ( this->nieb_.has_value() ) {

      return this->nieb_.value();
    }
    else {

      #ifndef NDEBUG
      this->verifyIndex( index );
      #endif
      return this->IXSS( this->NE() + index );
    }
  }

  /**
   *  @brief Return the number of secondary energies for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t numberOutgoingEnergies( std::size_t index ) const {

    return this->NIEB( index );
  }

  /**
   *  @brief Return all angular distribution data
   */
  const std::vector< std::vector< AngularDistributionData > >& data() const {

    return this->data_;
  }

  /**
   *  @brief Return the discrete cosine data for an incident and outgoing energy
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] incident    the incident energy index (one-based)
   *  @param[in] outgoing    the outgoing energy index (one-based)
   */
  auto discreteCosineData( std::size_t incident, std::size_t outgoing ) const {

    #ifndef NDEBUG
    this->verifyIndices( incident, outgoing );
    #endif
    return this->data_[ incident - 1 ][ outgoing - 1 ];
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ITXE = InelasticAngularDistributionBlock;

} // thermal namespace
} // ACEtk namespace
} // njoy namespace

#endif
