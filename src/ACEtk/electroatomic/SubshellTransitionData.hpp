#ifndef NJOY_ACETK_ELECTROATOMIC_SUBSHELLTRANSITIONDATA
#define NJOY_ACETK_ELECTROATOMIC_SUBSHELLTRANSITIONDATA

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

/**
 *  @class
 *  @brief The electron transition data for a given subshell
 *
 *  This block is part of the eprdata formats.
 *
 *  The SubshellTransitionData class contains the transition data
 *  to fill vacancies in the given subshell. Each transition has the following
 *  information associated to it:
 *    - the primary subshell designator (the designator of the subshell from
 *      where the electron is "moving" from)
 *    - the secondary subshell designator (the designator of the subshell from
 *      which the emitted electron is ejected or 0 for a radiative transition
 *      that only emits a photon)
 *    - the energy of the emitted photon or electron
 *    - the cumulative probability of the transition
 *
 *  The size NT of each (the total number of transitions) is stored in the SUBSH
 *  block. This data block may be empty (NT = 0).
 */
class SubshellTransitionData : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

  static std::size_t calculateNumberTransitions( Iterator begin, Iterator end ) {

    const auto size = std::distance( begin, end );

    if ( size%4 != 0 ) {

      Log::error( "The size of the transition data xss arry should be multiples of 4" );
      Log::info( "XSS size: {}", size );
      throw std::exception();
    }

    return size / 4;
  }

  static std::vector< std::vector< double > > generateArrays(
      std::vector< unsigned int > primary,
      std::vector< unsigned int > secondary,
      std::vector< double > energies,
      std::vector< double > probabilities ) {

    const auto nt = primary.size();

    if ( ( secondary.size() != nt ) || ( energies.size() != nt ) ||
         ( probabilities.size() != nt ) ) {

      Log::error( "The sizes of the transition data arrays are not consistent" );
      Log::info( "primary.size(): {}", nt );
      Log::info( "secondary.size(): {}", secondary.size() );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "probabilities.size(): {}", probabilities.size() );
      throw std::exception();
    }

    std::vector< std::vector< double > > arrays;

    for ( unsigned int index = 0; index < nt; ++index ) {

      std::vector< double > data( 4 );
      data[0] = static_cast< double >( primary[index] );
      data[1] = static_cast< double >( secondary[index] );
      data[2] = energies[index];
      data[3] = probabilities[index];
      arrays.emplace_back( std::move( data ) );
    }

    return arrays;
  }

public:

  /* constructor */

  SubshellTransitionData() = default;

  SubshellTransitionData( const SubshellTransitionData& ) = default;
  SubshellTransitionData( SubshellTransitionData&& ) = default;

  SubshellTransitionData& operator=( const SubshellTransitionData& ) = default;
  SubshellTransitionData& operator=( SubshellTransitionData&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] primary          the primary subshell designators
   *  @param[in] secondary        the secondary subshell designators
   *  @param[in] energies         the energy values of the secondary photon or electron
   *  @param[in] probabilities    the cumulative probabilities of the transitions
   */
  SubshellTransitionData(
      std::vector< unsigned int > primary,
      std::vector< unsigned int > secondary,
      std::vector< double > energies,
      std::vector< double > probabilities ) :
    ArrayData( "TRAN",
               generateArrays( std::move( primary ), std::move( secondary ),
                               std::move( energies ), std::move( probabilities ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the transition data in the XSS array
   *  @param[in] end     the end iterator of the transition data in the XSS array
   *  @param[in] nt      the number of transitions
   */
  SubshellTransitionData( Iterator begin, Iterator end ) :
    ArrayData( "TRAN", begin, end, 4, calculateNumberTransitions( begin, end ) ) {}

  /* methods */

  /**
   *  @brief Return the number of transitions
   */
  unsigned int NT() const { return this->M(); }

  /**
   *  @brief Return the number of transitions
   */
  unsigned int numberTransitions() const { return this->NT(); }

  /**
   *  @brief Return the transition data for a given transition
   *
   *  @param[in] index      the transition index (one-based)
   */
  auto transition( std::size_t index ) const {

    return this->darray( index );
  }

  /**
   *  @brief Return the primary designator for a given transition
   *
   *  @param[in] index      the transition index (one-based)
   */
  unsigned int primaryDesignator( std::size_t index ) const {

    return this->ivalue( index, 1 );
  }

  /**
   *  @brief Return the secondary designator for a given transition
   *
   *  @param[in] index      the transition index (one-based)
   */
  unsigned int secondaryDesignator( std::size_t index ) const {

    return this->ivalue( index, 2 );
  }

  /**
   *  @brief Return the energy of the emitted photon or electron for a given
   *         transition
   *
   *  @param[in] index      the transition index (one-based)
   */
  double energy( std::size_t index ) const {

    return this->dvalue( index, 3 );
  }

  /**
   *  @brief Return the cumulative probability for a given transition
   *
   *  @param[in] index      the transition index (one-based)
   */
  double probability( std::size_t index ) const {

    return this->dvalue( index, 4 );
  }

  /**
   *  @brief Return whether or not the transition is a radiative transitions
   *
   *  @param[in] index      the transition index (one-based)
   */
  bool isRadiativeTransition( std::size_t index ) const {

    return 0 == this->secondaryDesignator( index );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using TRAN = SubshellTransitionData;

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
