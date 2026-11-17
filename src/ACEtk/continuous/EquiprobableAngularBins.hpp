#ifndef NJOY_ACETK_CONTINUOUS_EQUIPROBABLEANGULARBINS
#define NJOY_ACETK_CONTINUOUS_EQUIPROBABLEANGULARBINS

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Equiprobable angular bin data for a single incident energy value
 *
 *  The EquiprobableAngularBins class contains the cosine values that make up
 *  the equiprobable bins (there are 33 values for defining 32 bins) for the
 *  assocoiated incident energy. It is used in the AND block. This
 *  format is only used in old ACE data.
 */
class EquiprobableAngularBins : protected base::Base {

  /* fields */

  double energy_ = 0.0;

  /* auxiliary functions */

  static void verifySize( std::size_t size ) {

    if ( size < 33 ) {

      Log::error( "The size of the XSS subrange in the equiprobable cosine bins "
                  "should be at least 33 (for 32 bins)" );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  static void verifySize( Iterator begin, Iterator end ) {

    auto size = std::distance( begin, end );
    verifySize( size );
  }

public:

  /* constructor */

  EquiprobableAngularBins() = default;

  EquiprobableAngularBins( const EquiprobableAngularBins& ) = default;
  EquiprobableAngularBins( EquiprobableAngularBins&& ) = default;

  EquiprobableAngularBins& operator=( const EquiprobableAngularBins& ) = default;
  EquiprobableAngularBins& operator=( EquiprobableAngularBins&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energy     the associated energy value
   *  @param[in] cosines    the cosine values (33 values)
   */
  EquiprobableAngularBins( double energy, std::vector< double > cosines ) :
    Base( "EquiprobableAngularBins", std::move( cosines ) ),
    energy_( energy ) {

    verifySize( this->XSS().size() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] energy     the associated energy value
   *  @param[in] begin      the begin iterator of the equiprobable bin data
   *  @param[in] end        the end iterator of the equiprobable bin data
   */
  EquiprobableAngularBins( double energy, Iterator begin, Iterator end ) :
    Base( "EquiprobableAngularBins", begin, end ),
    energy_( energy ) {

    verifySize( this->begin(), this->end() );
  }

  /**
   *  @brief Return the associated energy value
   */
  double energy() const { return this->energy_; }

  /**
   *  @brief Return the number of equiprobable angular bins
   */
  static constexpr int numberBins() { return 32; }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const {

    return this->XSS( 1, this->numberBins() + 1 );
  }

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
