#ifndef NJOY_ACETK_PHOTOATOMIC_FLUORESCENCEDATABLOCK
#define NJOY_ACETK_PHOTOATOMIC_FLUORESCENCEDATABLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief The photoatomic JFLO block with the fluorescence data
 *
 *  The FluorescenceDataBlock class contains 4 arrays of the
 *  same length:
 *    - the fluoresence edge energies
 *    - the relative ejection probabilities
 *    - the yields
 *    - the fluorescent energies
 *
 *  The size of each (the total number of fluorescence edges) is stored in NXS(4).
 */
class FluorescenceDataBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  FluorescenceDataBlock() = default;

  FluorescenceDataBlock( const FluorescenceDataBlock& ) = default;
  FluorescenceDataBlock( FluorescenceDataBlock&& ) = default;

  FluorescenceDataBlock& operator=( const FluorescenceDataBlock& ) = default;
  FluorescenceDataBlock& operator=( FluorescenceDataBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] edges            the edge energies
   *  @param[in] probabilities    the ejection probabilities
   *  @param[in] yields           the yields
   *  @param[in] energies         the fluorescent energies
   */
  FluorescenceDataBlock( std::vector< double > edges,
                         std::vector< double > probabilities,
                         std::vector< double > yields,
                         std::vector< double > energies ) :
    ArrayData( "JFLO",
               std::vector< std::vector< double > > {
                 std::move( edges ), std::move( probabilities ),
                 std::move( yields ), std::move( energies ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the JFLO block in the XSS array
   *  @param[in] end     the end iterator of the JFLO block in the XSS array
   *  @param[in] nflo    the number of edges
   */
  FluorescenceDataBlock( Iterator begin, Iterator end, unsigned int nflo ) :
    ArrayData( "JFLO", begin, end, nflo, 4 ) {}

  /**
   *  @brief Return the number of fluorescence edges
   */
  unsigned int NFLO() const { return this->N(); }

  /**
   *  @brief Return the number of fluorescence edges
   */
  unsigned int numberFluorescenceEdges() const { return this->NFLO(); }

  /**
   *  @brief Return the fluoresence edge energies
   */
  auto E() const { return this->darray( 1 ); }

  /**
   *  @brief Return the fluoresence edge energies
   */
  auto fluorescenceEdgeEnergies() const { return this->E(); }

  /**
   *  @brief Return the relative ejection probabilities
   */
  auto PHI() const { return this->darray( 2 ); }

  /**
   *  @brief Return the relative ejection probabilities
   */
  auto relativeEjectionProbabilities() const { return this->PHI(); }

  /**
   *  @brief Return the yields
   */
  auto Y() const { return this->darray( 3 ); }

  /**
   *  @brief Return the yields
   */
  auto yields() const { return this->Y(); }

  /**
   *  @brief Return the fluorescent energies
   */
  auto F() const { return this->darray( 4 ); }

  /**
   *  @brief Return the fluorescent energies
   */
  auto fluorescentEnergies() const { return this->F(); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using JFLO = FluorescenceDataBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
