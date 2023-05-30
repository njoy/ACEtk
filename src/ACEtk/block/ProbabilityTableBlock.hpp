#ifndef NJOY_ACETK_BLOCK_PROBABILITYTABLEBLOCK
#define NJOY_ACETK_BLOCK_PROBABILITYTABLEBLOCK

// system includes

// other includes
#include "ACEtk/block/ProbabilityTable.hpp"
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy UNR block with the unresolved resonance
 *         probability tables
 */
class ProbabilityTableBlock : protected details::Base {

  /* fields */
  std::vector< ProbabilityTable > data_;

  /* auxiliary functions */
  #include "ACEtk/block/ProbabilityTableBlock/src/generateXSS.hpp"
  #include "ACEtk/block/ProbabilityTableBlock/src/generateBlocks.hpp"
  #include "ACEtk/block/ProbabilityTableBlock/src/verifyIndex.hpp"

public:

  /* constructor */
  #include "ACEtk/block/ProbabilityTableBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of incident energy values
   */
  unsigned int N() const {

    return this->empty() ? 0 : static_cast< unsigned int >( this->XSS( 1 ) );
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

    return this->empty() ? 0 : static_cast< unsigned int >( this->XSS( 2 ) );
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

    return this->empty() ? 0 : static_cast< unsigned int >( this->XSS( 3 ) );
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

    return this->empty() ? 0 : static_cast< int >( this->XSS( 4 ) );
  }

  /**
   *  @brief Return the inelastic competition flag
   */
  int inelasticCompetion() const {

    return this->ILF();
  }

  /**
   *  @brief Return the absorption competition flag
   */
  int IOA() const {

    return this->empty() ? 0 : static_cast< int >( this->XSS( 5 ) );
  }

  /**
   *  @brief Return the inelastic competition flag
   */
  int absorptionCompetion() const {

    return this->IOA();
  }

  /**
   *  @brief Return the table type (values or multipliers)
   */
  unsigned int IFF() const {

    return this->empty() ? 0 : static_cast< unsigned int >( this->XSS( 6 ) );
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

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
