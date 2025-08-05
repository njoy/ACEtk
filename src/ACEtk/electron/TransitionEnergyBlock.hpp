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
  #include "ACEtk/electron/TransitionEnergyBlock/src/ctor.hpp"
  
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
   *  @brief Return the lower bremsstrahlung extrapolation transition energy
   */
  auto lowerBremsstrahlungTransitionEnergy() const {
    
    return ( this->N() > 2 ) ? std::optional< auto > { this->dvalue(1, 3) } : std::nullopt;
  }
  
  /**
   *  @brief Return the upper bremsstrahlung extrapolation transition energy
   */
  auto upperBremsstrahlungTransitionEnergy() const {
    
    return ( this->N() > 2 ) ? std::optional< auto > { this->dvalue(1, 4) } : std::nullopt;
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
