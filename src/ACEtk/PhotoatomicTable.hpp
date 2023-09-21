#ifndef NJOY_ACETK_PHOTOATOMICTABLE
#define NJOY_ACETK_PHOTOATOMICTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/block/PhotoatomicPrincipalCrossSectionBlock.hpp"
#include "ACEtk/block/IncoherentScatteringFunctionBlock.hpp"
#include "ACEtk/block/CoherentFormFactorBlock.hpp"
#include "ACEtk/block/PhotoatomicFluorescenceDataBlock.hpp"
#include "ACEtk/block/PhotoatomicHeatingNumbersBlock.hpp"
#include "ACEtk/block/PhotoatomicElectronShellBlock.hpp"
#include "ACEtk/block/PhotoatomicComptonProfileBlock.hpp"
#include "ACEtk/block/PhotoatomicElectronSubshellBlock.hpp"
#include "ACEtk/block/PhotoelectricCrossSectionBlock.hpp"
#include "ACEtk/block/PhotoatomicSubshellTransitionDataBlock.hpp"
#include "ACEtk/block/PhotoatomicElectronCrossSectionBlock.hpp"
#include "ACEtk/block/ElectronElasticAngularDistributionBlock.hpp"
#include "ACEtk/block/ElectronEnergyDistributionBlock.hpp"
#include "ACEtk/block/PhotoatomicElectronExcitationBlock.hpp"
#include "ACEtk/block/PhotoatomicElectronBremsstrahlungBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The photoatomic ACE table
 *
 *  The PhotoatomicTable class represents the ACE table for the photoatomic data.
 */
class PhotoatomicTable : protected Table {

  /* fields */
  block::ESZG eszg_;
  block::JINC jinc_;
  block::JCOH jcoh_;
  std::optional< block::JFLO > jflo_;
  block::LHNM lhnm_;
  std::optional< block::EPS > eps_;
  std::optional< block::SWD > swd_;
  std::optional< block::SUBSH > subsh_;
  std::optional< block::SPHEL > sphel_;
  std::optional< block::XPROB > xprob_;
  std::optional< block::ESZE > esze_;
  std::optional< block::EXCIT > excit_;
  std::optional< block::ELAS > elas_;
  std::vector< block::EION > eion_;
  std::optional< block::BREME > breme_;
  std::optional< block::BREML > breml_;

  /* auxiliary functions */
  #include "ACEtk/PhotoatomicTable/src/generateBlocks.hpp"
  #include "ACEtk/PhotoatomicTable/src/generateData.hpp"
  #include "ACEtk/PhotoatomicTable/src/verifyType.hpp"
  #include "ACEtk/PhotoatomicTable/src/verifySubshellIndex.hpp"

public:

  #include "ACEtk/PhotoatomicTable/src/ctor.hpp"

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
   *  @brief Return the total length of the XSS array
   */
  unsigned int length() const { return this->data().NXS(1); }

  /**
   *  @brief Return the atom number of the element
   */
  unsigned int Z() const { return this->data().NXS(2); }

  /**
   *  @brief Return the atom number of the element
   */
  unsigned int atomNumber() const { return this->Z(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->data().NXS(3); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the number of fluorescence edges
   */
  unsigned int NFLO() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of fluorescence edges
   */
  unsigned int numberFluorescenceEdges() const { return this->NFLO(); }

  /**
   *  @brief Return the number of electron shells (for Compton Doppler broadening)
   */
  unsigned int NSH() const { return this->data().NXS(5); }

  /**
   *  @brief Return the number of electron shells (for Compton Doppler broadening)
   */
  unsigned int numberElectronShells() const { return this->NSH(); }

  /**
   *  @brief Return the EPR data format flag (0 for old format, 1 for EPR data
   *         from 2012 and 3 for EPR data from 2014)
   */
  unsigned int NEPR() const { return this->data().NXS(6); }

  /**
   *  @brief Return the EPR data format flag (0 for old format, 1 for EPR data
   *         from 2012 and 3 for EPR data from 2014)
   */
  unsigned int electronPhotonRelaxationFormat() const { return this->NEPR(); }

  /**
   *  @brief Return the number of electron subshells (for photoelectric and electron
   *         impact ionization)
   */
  unsigned int NSSH() const { return this->data().NXS(7); }

  /**
   *  @brief Return the number of electron subshells (for photoelectric and electron
   *         impact ionization)
   */
  unsigned int numberElectronSubshells() const { return this->NSSH(); }

  /**
   *  @brief Return the number of electron energy points
   */
  unsigned int NE() const { return this->data().NXS(8); }

  /**
   *  @brief Return the number of electron energy points
   */
  unsigned int numberElectronEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the number of electron excitation energy points
   */
  unsigned int NXL() const { return this->data().NXS(9); }

  /**
   *  @brief Return the number of electron excitation energy points
   */
  unsigned int numberElectronExcitationEnergyPoints() const { return this->NXL(); }

  /**
   *  @brief Return the number of energy points with electron elastic angular
   *         distributions
   */
  unsigned int NA() const { return this->data().NXS(10); }

  /**
   *  @brief Return the number of energy points with electron elastic angular
   *         distributions
   */
  unsigned int numberElectronElasticEnergyPoints() const { return this->NA(); }

  /**
   *  @brief Return the number of energy points with Bremsstrahlung photon
   *         energy distributions
   */
  unsigned int NB() const { return this->data().NXS(11); }

  /**
  *  @brief Return the number of energy points with Bremsstrahlung photon
  *         energy distributions
   */
  unsigned int numberPhotonBremsstrahlungEnergyPoints() const { return this->NB(); }

  /**
   *  @brief Return the number of electron Bremsstrahlung energy points
   */
  unsigned int NBL() const { return this->data().NXS(12); }

  /**
   *  @brief Return the number of electron Bremsstrahlung energy points
   */
  unsigned int numberElectronBremsstrahlungEnergyPoints() const { return this->NBL(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the principal cross section block
   */
  const block::ESZG& ESZG() const { return this->eszg_; }

  /**
   *  @brief Return the principal cross section block
   */
  const block::ESZG& principalCrossSectionBlock() const { return this->ESZG(); }

  /**
   *  @brief Return the incoherent scattering function block
   */
  const block::JINC& JINC() const { return this->jinc_; }

  /**
   *  @brief Return the incoherent scattering function block
   */
  const block::JINC& incoherentScatteringFunctionBlock() const {

    return this->JINC();
  }

  /**
   *  @brief Return the coherent form factor block
   */
  const block::JCOH& JCOH() const { return this->jcoh_; }

  /**
   *  @brief Return the coherent form factor block
   */
  const block::JCOH& coherentFormFactorBlock() const { return this->JCOH(); }

  /**
   *  @brief Return the fluoresence data block
   */
  const std::optional< block::JFLO >& JFLO() const { return this->jflo_; }

  /**
   *  @brief Return the fluoresence data block
   */
  const std::optional< block::JFLO >& fluorescenceDataBlock() const {

    return this->JFLO();
  }

  /**
   *  @brief Return the heating numbers block
   */
  const block::LHNM& LHNM() const { return this->lhnm_; }

  /**
   *  @brief Return the heating numbers block
   */
  const block::LHNM& heatingNumbersBlock() const { return this->LHNM(); }

  /**
   *  @brief Return the electron shell block
   */
  const std::optional< block::EPS >& EPS() const { return this->eps_; }

  /**
   *  @brief Return the electron shell block
   */
  const std::optional< block::EPS >& electronShellBlock() const {

    return this->EPS();
  }

  /**
   *  @brief Return the compton profile block
   */
  const std::optional< block::SWD >& SWD() const { return this->swd_; }

  /**
   *  @brief Return the compton profile block
   */
  const std::optional< block::SWD >& comptonProfileBlock() const {

    return this->SWD();
  }

  /**
   *  @brief Return the electron subshell data block for eprdata (NEPR > 0)
   */
  const std::optional< block::SUBSH >& SUBSH() const { return this->subsh_; }

  /**
   *  @brief Return the electron subshell data block for eprdata (NEPR > 0)
   */
  const std::optional< block::SUBSH >& electronSubshellBlock() const {

    return this->SUBSH();
  }

  /**
   *  @brief Return the photoelectric cross section block for eprdata (NEPR > 0)
   */
  const std::optional< block::SPHEL >& SPHEL() const { return this->sphel_; }

  /**
   *  @brief Return the photoelectric cross section block for eprdata (NEPR > 0)
   */
  const std::optional< block::SPHEL >& photoelectricCrossSectionBlock() const {

    return this->SPHEL();
  }

  /**
   *  @brief Return the subshell transition data block for eprdata (NEPR > 0)
   */
  const std::optional< block::XPROB >& XPROB() const { return this->xprob_; }

  /**
   *  @brief Return the subshell transition data block for eprdata (NEPR > 0)
   */
  const std::optional< block::XPROB >& subshellTransitionDataBlock() const {

    return this->XPROB();
  }

  /**
   *  @brief Return the electron cross section block for eprdata (NEPR > 0)
   */
  const std::optional< block::ESZE >& ESZE() const { return this->esze_; }

  /**
   *  @brief Return the electron cross section block for eprdata (NEPR > 0)
   */
  const std::optional< block::ESZE >& electronCrossSectionBlock() const {

    return this->ESZE();
  }

  /**
   *  @brief Return the electron excitation energy loss block for eprdata (NEPR > 0)
   */
  const std::optional< block::EXCIT >& EXCIT() const { return this->excit_; }

  /**
   *  @brief Return the electron excitation energy loss block for eprdata (NEPR > 0)
   */
  const std::optional< block::EXCIT >& electronExcitationEnergyLossBlock() const {

    return this->EXCIT();
  }

  /**
   *  @brief Return the electron elastic angular distribution block for eprdata (NEPR > 0)
   */
  const std::optional< block::ELAS >& ELAS() const { return this->elas_; }

  /**
   *  @brief Return the electron elastic angular distribution block for eprdata (NEPR > 0)
   */
  const std::optional< block::ELAS >& electronElasticAngularDistributionBlock() const {

    return this->ELAS();
  }

  /**
   *  @brief Return the knock-on electron energy distribution block for a subshell
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const block::EION& EION( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifySubshellIndex( index );
    #endif
    return this->eion_[ index - 1 ];
  }

  /**
   *  @brief Return the knock-on electron energy distribution block for a subshell
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const block::EION& electroionisationEnergyDistributionBlock( std::size_t index ) const {

    return this->EION( index );
  }

  /**
   *  @brief Return the Bremsstrahlung energy distribution block for eprdata (NEPR > 0)
   */
  const std::optional< block::BREME >& BREME() const { return this->breme_; }

  /**
   *  @brief Return the Bremsstrahlung energy distribution block for eprdata (NEPR > 0)
   */
  const std::optional< block::BREME >& electronBremsstrahlungEnergyDistributionBlock() const {

    return this->BREME();
  }

  /**
   *  @brief Return the electron energy after Brehmsstrahlung block for eprdata (NEPR > 0)
   */
  const std::optional< block::BREML >& BREML() const { return this->breml_; }

  /**
   *  @brief Return the electron energy after Brehmsstrahlung block for eprdata (NEPR > 0)
   */
  const std::optional< block::BREML >& electronEnergyAfterBremsstrahlungBlock() const {

    return this->BREML();
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
