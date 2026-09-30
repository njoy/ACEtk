#ifndef NJOY_ACETK_ELECTRON_TRANSITIONENERGYBLOCK
#define NJOY_ACETK_ELECTRON_TRANSITIONENERGYBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron EKT block with the transition energy data
 *
 *  This block is part of el and el03 formats.
 *
 *  The TransitionEnergyBlock class contains 2 or 4 data points:
 *    - The K edge energy below which no electron induced relaxation will
 *      occur (EDG)
 *    - The K x-ray or Auger electron emission energy (EEK)
 *    - The (2) bremsstrahlung extrapolation transition points (NEL != 3)
 */
class TransitionEnergyBlock : protected base::ArrayData {
  // Use of the ArrayData base class is something of a kludge. Ideally,
  // this class would cimply contain 2 or 4 floating-point data members
  // but there does not seem to be an ACEtk base class for this case.

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */

  TransitionEnergyBlock() = default;

  TransitionEnergyBlock( const TransitionEnergyBlock& ) = default;
  TransitionEnergyBlock( TransitionEnergyBlock&& ) = default;

  TransitionEnergyBlock& operator=( const TransitionEnergyBlock& ) = default;
  TransitionEnergyBlock& operator=( TransitionEnergyBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] values    the various transition energy values
   */
  TransitionEnergyBlock( std::vector< double > values ) :
    ArrayData( "EKT",
               std::vector< std::vector< double > >{ std::move( values ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the EKT block in the XSS array
   *  @param[in] end     the end iterator of the EKT block in the XSS array
   *  @param[in] nel     the el data format flag (0 or 3)
   */
  TransitionEnergyBlock( Iterator begin, Iterator end, unsigned int nel ) :
    ArrayData( "EKT", begin, end, (nel == 3) ? 2 : 4, 1 ) {}
  
  /* methods */
  
  /**
   *  @brief Return the K edge energy
   */
  auto EDG() const { return this->dvalue(1, 1); }
  
  /**
   *  @brief Return the K edge energy
   */
  auto kEdgeEnergy() const { return this->EDG(); }
  
  /**
   *  @brief Return the K x-ray or Auger electron emission energy
   */
  auto EEK() const { return this->dvalue(1, 2); }
  
  /**
   *  @brief Return the K x-ray or Auger electron emission energy
   */
  auto kXrayEmissionEnergy() const { return this->EEK(); }
  
  /**
   *  @brief Return the upper bremsstrahlung extrapolation transition energy
   */
  auto upperBremsstrahlungTransitionEnergy() const {
    
    return ( this->N() > 2 )
           ? std::optional< double > { this->dvalue(1, 3) }
           : std::nullopt;
  }
  
  /**
   *  @brief Return the lower bremsstrahlung extrapolation transition energy
   */
  auto lowerBremsstrahlungTransitionEnergy() const {
    
    return ( this->N() > 2 )
           ? std::optional< double > { this->dvalue(1, 4) }
           : std::nullopt;
  }
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using EKT = TransitionEnergyBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
