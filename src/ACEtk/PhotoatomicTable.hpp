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

  /* auxiliary functions */
  #include "ACEtk/PhotoatomicTable/src/generateBlocks.hpp"
  #include "ACEtk/PhotoatomicTable/src/generateData.hpp"
  #include "ACEtk/PhotoatomicTable/src/verifyType.hpp"

public:

  #include "ACEtk/PhotoatomicTable/src/ctor.hpp"

  using Table::header;
  using Table::data;
  using Table::print;

  /**
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const { return this->header().ZAID(); }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double AWR() const { return this->header().AWR(); }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double atomicWeightRatio() const { return this->header().atomicWeightRatio(); }

  /**
   *  @brief Return the temperature of the table
   */
  double TEMP() const { return this->header().TEMP(); }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->header().temperature(); }

  /**
   *  @brief Return the date
   */
  const std::string& date() const { return this->header().date(); }

  /**
   *  @brief Return the title
   */
  const std::string& title() const { return this->header().title(); }

  /**
   *  @brief Return the material
   */
  const std::string& material() const { return this->header().material(); }

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
   *  @brief Return the number of electron shells
   */
  unsigned int NSH() const { return this->data().NXS(5); }

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int numberElectronShells() const { return this->NSH(); }

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
};

} // ACEtk namespace
} // njoy namespace

#endif
