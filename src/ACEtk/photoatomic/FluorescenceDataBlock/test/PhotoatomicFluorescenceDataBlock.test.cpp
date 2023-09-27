#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/photoatomic/FluorescenceDataBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PhotoatomicFluorescenceDataBlock = block::PhotoatomicFluorescenceDataBlock;

std::vector< double > chunk();
void verifyChunk( const PhotoatomicFluorescenceDataBlock& );

SCENARIO( "PhotoatomicFluorescenceDataBlock" ) {

  GIVEN( "valid data for a PhotoatomicFluorescenceDataBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > edges = { 1.294500000000E-03,  1.294500000000E-03 };
      std::vector< double > probabilities = { 8.180862310960E-02,  1.000000000000E+00 };
      std::vector< double > yields = { 0.000000000000E+00,  2.542671170140E-02 };
      std::vector< double > energies = { 0.000000000000E+00,  1.238156190380E-03 };

      PhotoatomicFluorescenceDataBlock chunk( std::move( edges ),
                                              std::move( probabilities ),
                                              std::move( yields ),
                                              std::move( energies ) );

      THEN( "a PhotoatomicFluorescenceDataBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      PhotoatomicFluorescenceDataBlock chunk( xss.begin(), xss.end(), 2 );

      THEN( "a PhotoatomicFluorescenceDataBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

    1.294500000000E-03,  1.294500000000E-03,  8.180862310960E-02,  1.000000000000E+00,
    0.000000000000E+00,  2.542671170140E-02,  0.000000000000E+00,  1.238156190380E-03  };
}

void verifyChunk( const PhotoatomicFluorescenceDataBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 8 == chunk.length() );
  CHECK( "JFLO" == chunk.name() );

  CHECK( 8 == chunk.XSS().size() );

  CHECK( 2 == chunk.NFLO() );
  CHECK( 2 == chunk.numberFluorescenceEdges() );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.PHI().size() );
  CHECK( 2 == chunk.Y().size() );
  CHECK( 2 == chunk.F().size() );
  CHECK( 2 == chunk.fluorescenceEdgeEnergies().size() );
  CHECK( 2 == chunk.relativeEjectionProbabilities().size() );
  CHECK( 2 == chunk.yields().size() );
  CHECK( 2 == chunk.fluorescentEnergies().size() );

  CHECK( 1.294500000000E-03 == Approx( chunk.E().front() ) );
  CHECK( 1.294500000000E-03 == Approx( chunk.E().back() ) );
  CHECK( 8.180862310960E-02 == Approx( chunk.PHI().front() ) );
  CHECK( 1.000000000000E+00 == Approx( chunk.PHI().back() ) );
  CHECK( 0.000000000000E+00 == Approx( chunk.Y().front() ) );
  CHECK( 2.542671170140E-02 == Approx( chunk.Y().back() ) );
  CHECK( 0.000000000000E+00 == Approx( chunk.F().front() ) );
  CHECK( 1.238156190380E-03 == Approx( chunk.F().back() ) );
  CHECK( 1.294500000000E-03 == Approx( chunk.fluorescenceEdgeEnergies().front() ) );
  CHECK( 1.294500000000E-03 == Approx( chunk.fluorescenceEdgeEnergies().back() ) );
  CHECK( 8.180862310960E-02 == Approx( chunk.relativeEjectionProbabilities().front() ) );
  CHECK( 1.000000000000E+00 == Approx( chunk.relativeEjectionProbabilities().back() ) );
  CHECK( 0.000000000000E+00 == Approx( chunk.yields().front() ) );
  CHECK( 2.542671170140E-02 == Approx( chunk.yields().back() ) );
  CHECK( 0.000000000000E+00 == Approx( chunk.fluorescentEnergies().front() ) );
  CHECK( 1.238156190380E-03 == Approx( chunk.fluorescentEnergies().back() ) );
}
