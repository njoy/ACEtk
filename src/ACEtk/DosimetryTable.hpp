#ifndef NJOY_ACETK_DOSIMETRYYTABLE
#define NJOY_ACETK_DOSIMETRYYTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/block/ReactionNumberBlock.hpp"
#include "ACEtk/block/DosimetryCrossSectionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The dosimetry ACE table
 *
 *  The DosimetryTable class represents the ACE table for dosimetry data.
 */
class DosimetryTable : protected Table {

  /* fields */
  block::MTR mtr_;
  block::SIGD sig_;

  /* auxiliary functions */
  void generateBlocks() {

    auto begin = this->data().XSS().begin();
    auto mtr = begin + this->data().JXS(3) - 1;
    auto lsig = begin + this->data().JXS(6) - 1;
    auto sig = begin + this->data().JXS(7) - 1;
    auto end = this->data().XSS().end();

    this->mtr_ = block::MTR( mtr, lsig, this->NTR() );
    this->sig_ = block::SIGD( lsig, sig, end, this->NTR() );
  }

public:

  #include "ACEtk/DosimetryTable/src/ctor.hpp"

  using Table::header;
  using Table::data;
  using Table::print;

  //! @todo projectile() function
  //! @todo target() function

  /**
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const { return this->header().ZAID(); }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->header().temperature();}

  // NXS information

  /**
   *  @brief Return the total length of the XSS array
   */
  unsigned int length() const { return this->data().NXS(1); }

  /**
   *  @brief Return the ZA of the target
   */
  unsigned int ZA() const { return this->data().NXS(2); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->data().NXS(3); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const { return this->NTR(); }

  /**
   *  @brief Return the total number of available reactions (including elastic)
   */
  unsigned int totalNumberReactions() const { return this->NTR() + 1; }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the reaction number block
   */
  const block::MTR& MTR() const { return this->mtr_; }

  /**
   *  @brief Return the reaction number block
   */
  const block::MTR& reactionNumberBlock() const { return this->MTR(); }

  /**
   *  @brief Return the cross section block
   */
  const block::SIGD& SIG() const { return this->sig_; }

  /**
   *  @brief Return the cross section block
   */
  const block::SIGD& crossSectionBlock() const { return this->SIG(); }
};

} // ACEtk namespace
} // njoy namespace

#endif
