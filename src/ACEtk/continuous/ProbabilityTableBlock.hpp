#ifndef NJOY_ACETK_CONTINUOUS_PROBABILITYTABLEBLOCK
#define NJOY_ACETK_CONTINUOUS_PROBABILITYTABLEBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/continuous/ProbabilityTable.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy UNR block with the unresolved resonance
 *         probability tables
 */
class ProbabilityTableBlock : protected base::Base {

  /* fields */

  std::vector< ProbabilityTable > data_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( unsigned int interpolation, int inelastic,
               int absorption, unsigned int type,
               std::vector< ProbabilityTable >&& tables ) {

    std::vector< double > xss( 6 + tables.size() );
    const auto bins = tables.front().numberBins();
    xss[0] = static_cast< double >( tables.size() );
    xss[1] = static_cast< double >( bins );
    xss[2] = static_cast< double >( interpolation );
    xss[3] = static_cast< double >( inelastic );
    xss[4] = static_cast< double >( absorption );
    xss[5] = static_cast< double >( type );
    unsigned int index = 6;
    for ( const auto& table : tables ) {

      xss[index] = table.incidentEnergy();
      xss.insert( xss.end(), table.begin(), table.end() );
      ++index;
    }
    return xss;
  }

  void generateBlocks() {

    this->data_.clear();

    std::size_t m = this->M();
    auto left = this->begin() + 6 + this->N();
    auto right = left;
    for ( unsigned int index = 1; index <= this->N(); ++index ) {

      right = left + 6 * m;
      this->data_.emplace_back( left, right, this->XSS( 6 + index ), m );
      left = right;
    }
  }

  void verifyIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->N() ) ) {

      Log::error( "Illegal index argument into the {} block", this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between 1 and {} inclusively",
                 this->name(), this->N() );
      throw std::out_of_range( this->name() );
    }
  }

public:

  /* constructor */

  ProbabilityTableBlock() = default;

  ProbabilityTableBlock( const ProbabilityTableBlock& base ) :
    Base( base ), data_( base.data_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  ProbabilityTableBlock( ProbabilityTableBlock&& base ) :
    Base( std::move( base ) ), data_( std::move( base.data_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  ProbabilityTableBlock& operator=( const ProbabilityTableBlock& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->data_ = base.data_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  ProbabilityTableBlock& operator=( ProbabilityTableBlock&& base ) {

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
   *  @param[in] interpolation    the interpolation type
   *  @param[in] inelastic        the inelastic competition flag
   *  @param[in] absorption       the absorption competition flag
   *  @param[in] type             the probability table type
   *  @param[in] tables           the probability tables
   */
  ProbabilityTableBlock( unsigned int interpolation, int inelastic,
                         int absorption, unsigned int type,
                         std::vector< ProbabilityTable > tables ) :
    Base( "UNR", generateXSS( interpolation, inelastic, absorption, type,
                              std::move( tables ) ) ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] bdd    the begin iterator of the BDD block in the XSS array
   *  @param[in] end    the end iterator of the BDD block in the XSS array
   *  @param[in] npcr   the number of delayed probability tables
   */
  ProbabilityTableBlock( Iterator bdd, Iterator end ) :
    Base( "UNR", bdd, end ) {

    this->generateBlocks();
  }

  /* methods */

  /**
   *  @brief Return the number of incident energy values
   */
  unsigned int N() const {

    return this->empty() ? 0 : static_cast< unsigned int >( this->IXSS( 1 ) );
  }

  /**
   *  @brief Return the number of incident energy values
   */
  unsigned int numberIncidentEnergies() const {

    return this->N();
  }

  /**
   *  @brief Return the number of bins in each table
   */
  unsigned int M() const {

    return this->empty() ? 0 : static_cast< unsigned int >( this->IXSS( 2 ) );
  }

  /**
   *  @brief Return the number of bins in each table
   */
  unsigned int numberBins() const {

    return this->M();
  }

  /**
   *  @brief Return the interpolation flag
   */
  unsigned int INT() const {

    return this->empty() ? 0 : static_cast< unsigned int >( this->IXSS( 3 ) );
  }

  /**
   *  @brief Return the interpolation flag
   */
  unsigned int interpolation() const {

    return this->INT();
  }

  /**
   *  @brief Return the inelastic competition flag
   */
  int ILF() const {

    return this->empty() ? 0 : static_cast< int >( this->IXSS( 4 ) );
  }

  /**
   *  @brief Return the inelastic competition flag
   */
  int inelasticCompetition() const {

    return this->ILF();
  }

  /**
   *  @brief Return the absorption competition flag
   */
  int IOA() const {

    return this->empty() ? 0 : static_cast< int >( this->IXSS( 5 ) );
  }

  /**
   *  @brief Return the absorption competition flag
   */
  int absorptionCompetition() const {

    return this->IOA();
  }

  /**
   *  @brief Return the table type (values or multipliers)
   */
  unsigned int IFF() const {

    return this->empty() ? 0 : static_cast< unsigned int >( this->IXSS( 6 ) );
  }

  /**
   *  @brief Return the table type (values or multipliers)
   */
  unsigned int type() const {

    return this->IFF();
  }

  /**
   *  @brief Return the incident energy values
   */
  auto energies() const {

    return this->XSS( 7, this->N() );
  }

  /**
   *  @brief Return the probability tables
   */
  const std::vector< ProbabilityTable >& data() const {

    return this->data_;
  }

  /**
   *  @brief Return the probability table for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const ProbabilityTable& probabilityTable( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIndex( index );
    #endif
    return this->data_[ index - 1 ];
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using UNR = ProbabilityTableBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
