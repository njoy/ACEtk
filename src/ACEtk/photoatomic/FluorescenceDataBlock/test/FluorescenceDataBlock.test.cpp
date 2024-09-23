// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/photoatomic/FluorescenceDataBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using FluorescenceDataBlock = photoatomic::FluorescenceDataBlock;

std::vector< double > chunk();
void verifyChunk( const FluorescenceDataBlock&, const std::vector< double >& );
FluorescenceDataBlock makeDummyBlock();

SCENARIO( "FluorescenceDataBlock" ) {

  GIVEN( "valid data for a FluorescenceDataBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > edges = { 1.294500000000E-03,  1.294500000000E-03 };
      std::vector< double > probabilities = { 8.180862310960E-02,  1.000000000000E+00 };
      std::vector< double > yields = { 0.000000000000E+00,  2.542671170140E-02 };
      std::vector< double > energies = { 0.000000000000E+00,  1.238156190380E-03 };

      FluorescenceDataBlock chunk( std::move( edges ),
                                   std::move( probabilities ),
                                   std::move( yields ),
                                   std::move( energies ) );

      THEN( "a FluorescenceDataBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      FluorescenceDataBlock chunk( xss.begin(), xss.end(), 2 );

      THEN( "a FluorescenceDataBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      FluorescenceDataBlock chunk( xss.begin(), xss.end(), 2 );
      FluorescenceDataBlock copy( chunk );

      THEN( "an FluorescenceDataBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      FluorescenceDataBlock chunk( xss.begin(), xss.end(), 2 );
      FluorescenceDataBlock move( std::move( chunk ) );

      THEN( "an FluorescenceDataBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      FluorescenceDataBlock chunk( xss.begin(), xss.end(), 2 );
      FluorescenceDataBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an FluorescenceDataBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      FluorescenceDataBlock chunk( xss.begin(), xss.end(), 2 );
      FluorescenceDataBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an FluorescenceDataBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

    1.294500000000E-03,  1.294500000000E-03,  8.180862310960E-02,  1.000000000000E+00,
    0.000000000000E+00,  2.542671170140E-02,  0.000000000000E+00,  1.238156190380E-03  };
}

void verifyChunk( const FluorescenceDataBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

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

  CHECK_THAT( 1.294500000000E-03, WithinRel( chunk.E().front() ) );
  CHECK_THAT( 1.294500000000E-03, WithinRel( chunk.E().back() ) );
  CHECK_THAT( 8.180862310960E-02, WithinRel( chunk.PHI().front() ) );
  CHECK_THAT( 1.000000000000E+00, WithinRel( chunk.PHI().back() ) );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.Y().front() ) );
  CHECK_THAT( 2.542671170140E-02, WithinRel( chunk.Y().back() ) );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.F().front() ) );
  CHECK_THAT( 1.238156190380E-03, WithinRel( chunk.F().back() ) );
  CHECK_THAT( 1.294500000000E-03, WithinRel( chunk.fluorescenceEdgeEnergies().front() ) );
  CHECK_THAT( 1.294500000000E-03, WithinRel( chunk.fluorescenceEdgeEnergies().back() ) );
  CHECK_THAT( 8.180862310960E-02, WithinRel( chunk.relativeEjectionProbabilities().front() ) );
  CHECK_THAT( 1.000000000000E+00, WithinRel( chunk.relativeEjectionProbabilities().back() ) );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.yields().front() ) );
  CHECK_THAT( 2.542671170140E-02, WithinRel( chunk.yields().back() ) );
  CHECK_THAT( 0.000000000000E+00, WithinRel( chunk.fluorescentEnergies().front() ) );
  CHECK_THAT( 1.238156190380E-03, WithinRel( chunk.fluorescentEnergies().back() ) );
}

FluorescenceDataBlock makeDummyBlock() {

  return { { 1., 2. }, { 3., 4. }, { 5., 6. }, { 7., 8. } };
}
