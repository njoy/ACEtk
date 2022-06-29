#ifndef NJOY_ACETK_THERMALSCATTERINGTABLE
#define NJOY_ACETK_THERMALSCATTERINGTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/block/ThermalScatteringCrossSectionBlock.hpp"
#include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock.hpp"
#include "ACEtk/block/ThermalScatteringElasticAngularDistributionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The thermal scattering ACE table
 *
 *  The ThermalScatteringTable class represents the ACE table for the thermal
 *  scattering data.
 */
class ThermalScatteringTable : protected Table {

  /* fields */
  block::ITIE itie_;
  block::ITXE itxe_;
  block::ITCE itce_;
  block::ITCA itca_;
  block::ITCEI itcei_;
  block::ITCAI itcai_;

  /* auxiliary functions */
  #include "ACEtk/ThermalScatteringTable/src/generateBlocks.hpp"
  #include "ACEtk/ThermalScatteringTable/src/generateData.hpp"
  #include "ACEtk/ThermalScatteringTable/src/verifyType.hpp"

public:

  #include "ACEtk/ThermalScatteringTable/src/ctor.hpp"

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
   *  @brief Return the inelastic scattering mode
   */
  unsigned int IDPNI() const { return this->data().NXS(2); }

  /**
   *  @brief Return the inelastic scattering mode
   */
  unsigned int inelasticScatteringMode() const { return this->IDPNI(); }

  /**
   *  @brief Return the inelastic dimensioning parameter
   */
  unsigned int NIL() const { return this->data().NXS(3); }

  /**
   *  @brief Return the inelastic dimensioning parameter
   */
  unsigned int inelasticDimensioningParameter() const { return this->NIL(); }

  /**
   *  @brief Return the number of inelastic outgoing energies
   */
  unsigned int NIEB() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of inelastic outgoing energies
   */
  unsigned int numberInelasticOutgoingEnergies() const { return this->NIEB(); }

  /**
   *  @brief Return the elastic scattering mode
   */
  unsigned int IDPNC() const { return this->data().NXS(5); }

  /**
   *  @brief Return the elastic scattering mode
   */
  unsigned int elasticScatteringMode() const { return this->IDPNC(); }

  /**
   *  @brief Return the first elastic dimensioning parameter
   */
  unsigned int NCL() const { return this->data().NXS(6); }

  /**
   *  @brief Return the first elastic dimensioning parameter
   */
  unsigned int firstElasticDimensioningParameter() const { return this->NCL(); }

  /**
   *  @brief Return the second elastic dimensioning parameter
   */
  unsigned int NCLI() const { return this->data().NXS(8); }

  /**
   *  @brief Return the first elastic dimensioning parameter
   */
  unsigned int secondElasticDimensioningParameter() const { return this->NCLI(); }

  /**
   *  @brief Return the secondary energy mode
   */
  unsigned int IFENG() const { return this->data().NXS(7); }

  /**
   *  @brief Return the secondary energy mode
   */
  unsigned int secondaryEnergyMode() const { return this->IFENG(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the inelastic thermal scattering cross section block
   */
  const block::ITIE& ITIE() const { return this->itie_; }

  /**
   *  @brief Return the inelastic thermal scattering cross section block
   */
  const block::ITIE& inelasticCrossSectionBlock() const {

    return this->ITIE();
  }

  /**
   *  @brief Return the inelastic thermal scattering angular distribution block
   */
  const block::ITXE& ITXE() const { return this->itxe_; }

  /**
   *  @brief Return the inelastic thermal scattering angular distribution block
   */
  const block::ITXE& inelasticAngularDistributionBlock() const {

    return this->ITXE();
  }

  /**
   *  @brief Return the coherent elastic thermal scattering cross section block
   */
  const block::ITCE& ITCE() const { return this->itce_; }

  /**
   *  @brief Return the coherent elastic thermal scattering cross section block
   */
  const block::ITCE& coherentElasticCrossSectionBlock() const {

    return this->ITCE();
  }

  /**
   *  @brief Return the coherent elastic thermal scattering angular distribution
   *         block
   */
  const block::ITCA& ITCA() const { return this->itca_; }

  /**
   *  @brief Return the coherent elastic thermal scattering angular distribution
   *         block
   */
  const block::ITCA& coherentElasticAngularDistributionBlock() const {

    return this->ITCA();
  }

  /**
   *  @brief Return the incoherent elastic thermal scattering cross section block
   */
  const block::ITCEI& ITCEI() const { return this->itcei_; }

  /**
   *  @brief Return the incoherent elastic thermal scattering cross section block
   */
  const block::ITCEI& incoherentElasticCrossSectionBlock() const {

    return this->ITCEI();
  }

  /**
   *  @brief Return the incoherent elastic thermal scattering angular distribution
   *         block
   */
  const block::ITCAI& ITCAI() const { return this->itcai_; }

  /**
   *  @brief Return the incoherent elastic thermal scattering angular distribution
   *         block
   */
  const block::ITCAI& incoherentElasticAngularDistributionBlock() const {

    return this->ITCAI();
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
