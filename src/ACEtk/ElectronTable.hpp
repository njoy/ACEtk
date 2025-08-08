#ifndef NJOY_ACETK_ELECTRONTABLE
#define NJOY_ACETK_ELECTRONTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/electron/BremsstrahlungAngularSpectrumBlock.hpp"
#include "ACEtk/electron/BremsstrahlungCorrectionFactorBlock.hpp"
#include "ACEtk/electron/BremsstrahlungEnergySpectrumBlock.hpp"
#include "ACEtk/electron/BremsstrahlungHighFrequencyBlock.hpp"
#include "ACEtk/electron/BremsstrahlungProductionBlock.hpp"
#include "ACEtk/electron/MottScatteringCorrectionBlock.hpp"
#include "ACEtk/electron/OscillatorBlock.hpp"
#include "ACEtk/electron/RadiationStoppingPowerBlock.hpp"
#include "ACEtk/electron/RileyCrossSectionBlock.hpp"
#include "ACEtk/electron/TransitionEnergyBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The electron ACE table
 *
 *  The ElectronTable class represents the ACE table for the electron data.
 */
class ElectronTable : protected Table {
  
  /* fields */
  electron::EKT ekt_;
  electron::RAD rad_;
  electron::MOT mot_;
  electron::RLY rly_;
  std::optional< electron::XSB > xsb_;
  std::optional< electron::CRB > crb_;
  std::optional< electron::HFB > hfb_;
  std::optional< electron::RKT > rkt_;
  std::optional< electron::RKA > rka_;
  std::optional< electron::OSC > osc_;
  
  /* auxiliary functions */
  #include "ACEtk/ElectronTable/src/generateBlocks.hpp"
  #include "ACEtk/ElectronTable/src/generateData.hpp"
  #include "ACEtk/ElectronTable/src/verifyType.hpp"
  
public:

  #include "ACEtk/ElectronTable/src/ctor.hpp"
  
  using Table::header;
  using Table::data;
  using Table::print;
  
  /**
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.ZAID(); },
                       this->header() );
  }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double AWR() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.AWR(); },
                       this->header() );
  }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double atomicWeightRatio() const { return this->AWR(); }

  /**
   *  @brief Return the temperature of the table
   */
  double TEMP() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.TEMP(); },
                       this->header() );
  }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->TEMP(); }

  /**
   *  @brief Return the date
   */
  const std::string& date() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.date(); },
                       this->header() );
  }

  // NXS information

  /**
   *  @brief Return the EL data format flag (0 or 3)
   */
  unsigned int NEL() const { return this->data().NXS( 16 ); }

  /**
   *  @brief Return the EL data format flag (0 or 3)
   */
  unsigned int electronDataFormat() const { return this->NEL(); }

  /**
   *  @brief Return the total length of the XSS array
   */
  unsigned int length() const { return this->data().NXS( 1 ); }

  /**
   *  @brief Return the atom number of the element
   */
  unsigned int Z() const { return this->data().NXS( 2 ); }

  /**
   *  @brief Return the atom number of the element
   */
  unsigned int atomNumber() const { return this->Z(); }

  /**
   *  @brief Return the isomeric state of the target
   */
  unsigned int S() const { return 0; }

  /**
   *  @brief Return the isomeric state of the target
   */
  unsigned int isomericState() const { return this->S(); }

  /**
   *  @brief Return the mass number of the target
   */
  unsigned int A() const { return 0; }

  /**
   *  @brief Return the mass number of the target
   */
  unsigned int massNumber() const { return this->A(); }

  /**
   *  @brief Return the number of radiation stopping power points
   */
  unsigned int NRAD() const { return this->data().NXS( 3 ); }

  /**
   *  @brief Return the number of radiation stopping power points
   */
  unsigned int numberRadiationStoppingPoints() const { return this->NRAD(); }

  /**
   *  @brief Return the number of Mott scattering correction points
   */
  unsigned int NMOT() const { return this->data().NXS( 4 ); }

  /**
   *  @brief Return the number of Mott scattering correction points
   */
  unsigned int numberMottCorrectionPoints() const { return this->NMOT(); }

  /**
   *  @brief Return the number of electron energy points for bremsstrahlung production (NEL == 3)
   */
  unsigned int NEB() const { return ( this->NEL() == 3 ) ? this->data().NXS( 5 ) : 0; }

  /**
   *  @brief Return the number of electron energy points for bremsstrahlung production (NEL == 3)
   */
  unsigned int numberElectronBremsstrahlungEnergyPoints() const { return this->NEB(); }

  /**
   *  @brief Return the number of photon ratio points for bremsstrahlung production (NEL == 3)
   */
  unsigned int NPB() const { return ( this->NEL() == 3 ) ? this->data().NXS( 6 ) : 0; }

  /**
   *  @brief Return the number of photon ratio points for bremsstrahlung production (NEL == 3)
   */
  unsigned int numberPhotonBremsstrahlungRatioPoints() const { return this->NPB(); }

  /**
   *  @brief Return the number of bremsstrahlung correction factor points (NEL != 3)
   */
  unsigned int NCRB() const { return ( this->NEL() != 3 ) ? this->data().NXS( 5 ) : 0; }

  /**
   *  @brief Return the number of bremsstrahlung correction factor points (NEL != 3)
   */
  unsigned int numberBremsstrahlungCorrectionPoints() const { return this->NCRB(); }

  /**
   *  @brief Return the number of bremsstrahlung high-frequency limit points (NEL != 3)
   */
  unsigned int NHFB() const { return ( this->NEL() != 3 ) ? this->data().NXS( 6 ) : 0; }

  /**
   *  @brief Return the number of bremsstrahlung high-frequency limit points (NEL != 3)
   */
  unsigned int numberBremsstrahlungHighFrequencyPoints() const { return this->NHFB(); }

  /**
   *  @brief Return the number of bremsstrahlung energy spectrum points (NEL == 3)
   */
  unsigned int NRKT() const { return ( this->NEL() == 3 ) ? this->data().NXS( 9 ) : 0; }

  /**
   *  @brief Return the number of bremsstrahlung energy spectrum points (NEL == 3)
   */
  unsigned int numberBremsstrahlungEnergyPoints() const { return this->NRKT(); }

  /**
   *  @brief Return the number of bremsstrahlung angular spectrum points (NEL == 3)
   */
  unsigned int NRKA() const { return ( this->NEL() == 3 ) ? this->data().NXS( 10 ) : 0; }

  /**
   *  @brief Return the number of bremsstrahlung angular spectrum points (NEL == 3)
   */
  unsigned int numberBremsstrahlungAngularPoints() const { return this->NRKA(); }

  /**
   *  @brief Return the number of oscillator points (NEL == 3)
   */
  unsigned int NOSC() const { return ( this->NEL() == 3 ) ? this->data().NXS( 11 ) : 0; }

  /**
   *  @brief Return the number of oscillator points (NEL == 3)
   */
  unsigned int numberOscillatorPoints() const { return this->NOSC(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the transition energy block
   */
  const electron::EKT& EKT() const { return this->ekt_; }

  /**
   *  @brief Return the radiation stopping power block
   */
  const electron::RAD& RAD() const { return this->rad_; }

  /**
   *  @brief Return the Mott scattering correction block
   */
  const electron::MOT& MOT() const { return this->mot_; }

  /**
   *  @brief Return the Riley cross section block
   */
  const electron::RLY& RLY() const { return this->rly_; }

  /**
   *  @brief Return the bremsstrahlung production block
   */
  const std::optional< electron::XSB >& XSB() const { return this->xsb_; }

  /**
   *  @brief Return the bremsstrahlung correction factor block
   */
  const std::optional< electron::CRB >& CRB() const { return this->crb_; }

  /**
   *  @brief Return the bremsstrahlung high-frequency block
   */
  const std::optional< electron::HFB >& HFB() const { return this->hfb_; }

  /**
   *  @brief Return the bremsstrahlung energy spectrum block
   */
  const std::optional< electron::RKT >& RKT() const { return this->rkt_; }

  /**
   *  @brief Return the bremsstrahlung angular spectrum block
   */
  const std::optional< electron::RKA >& RKA() const { return this->rka_; }

  /**
   *  @brief Return the oscillator block
   */
  const std::optional< electron::OSC >& OSC() const { return this->osc_; }
  
};

} // ACEtk namespace
} // njoy namespace

#endif