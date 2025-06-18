// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/ProbabilityTableBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ProbabilityTableBlock = continuous::ProbabilityTableBlock;
using ProbabilityTable = continuous::ProbabilityTable;

std::vector< double > chunk();
void verifyChunk( const ProbabilityTableBlock&, const std::vector< double >& );
ProbabilityTableBlock makeDummyBlock();

SCENARIO( "ProbabilityTableBlock" ) {

  GIVEN( "valid data for a ProbabilityTableBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      unsigned int interpolation = 2;
      int inelastic = -1;
      int absorption = 0;
      unsigned int type = 1;
      std::vector< ProbabilityTable > tables = {

        ProbabilityTable( 1e-3, { 0.5, 1.0 }, { 1., 2 }, { 3., 4. }, { 5., 6. },
                          { 7., 8. }, { 9., 10. } ),
        ProbabilityTable( 1e+3, { 0.25, 1.0 }, { 11., 12 }, { 13., 14. },
                          { 15., 16. }, { 17., 18. }, { 19., 20. } )
      };

      ProbabilityTableBlock chunk( interpolation, inelastic, absorption, type,
                                   std::move( tables ) );

      THEN( "a ProbabilityTable can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      ProbabilityTableBlock chunk( xss.begin(), xss.end() );

      THEN( "a ProbabilityTable can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      ProbabilityTableBlock chunk( xss.begin(), xss.end() );
      ProbabilityTableBlock copy( chunk );

      THEN( "an ProbabilityTableBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      ProbabilityTableBlock chunk( xss.begin(), xss.end() );
      ProbabilityTableBlock move( std::move( chunk ) );

      THEN( "an ProbabilityTableBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      ProbabilityTableBlock chunk( xss.begin(), xss.end() );
      ProbabilityTableBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an ProbabilityTableBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      ProbabilityTableBlock chunk( xss.begin(), xss.end() );
      ProbabilityTableBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an ProbabilityTableBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 2, 2, 2, -1, 0, 1, 1e-3, 1e+3,
           0.5, 1., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10.,
           0.25, 1.0, 11., 12., 13., 14., 15., 16., 17., 18., 19., 20. };
}

void verifyChunk( const ProbabilityTableBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 32 == chunk.length() );
  CHECK( "UNR" == chunk.name() );

  CHECK( 32 == chunk.XSS().size() );

  CHECK( 2 == chunk.N() );
  CHECK( 2 == chunk.numberIncidentEnergies() );
  CHECK( 2 == chunk.M() );
  CHECK( 2 == chunk.numberBins() );
  CHECK( 2 == chunk.INT() );
  CHECK( 2 == chunk.interpolation() );
  CHECK( -1 == chunk.ILF() );
  CHECK( -1 == chunk.inelasticCompetition() );
  CHECK( 0 == chunk.IOA() );
  CHECK( 0 == chunk.absorptionCompetition() );
  CHECK( 1 == chunk.IFF() );
  CHECK( 1 == chunk.type() );

  CHECK( 2 == chunk.energies().size() );
  CHECK_THAT( 1e-3, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 1e+3, WithinRel( chunk.energies()[1] ) );

  auto table1 = chunk.probabilityTable(1);
  CHECK_THAT( 1e-3, WithinRel( table1.incidentEnergy() ) );

  CHECK( 2 == table1.numberBins() );
  CHECK( 2 == table1.cumulativeProbabilities().size() );
  CHECK( 2 == table1.total().size() );
  CHECK( 2 == table1.elastic().size() );
  CHECK( 2 == table1.fission().size() );
  CHECK( 2 == table1.capture().size() );
  CHECK( 2 == table1.heating().size() );

  CHECK_THAT( 0.5, WithinRel( table1.cumulativeProbabilities().front() ) );
  CHECK_THAT( 1.0, WithinRel( table1.cumulativeProbabilities().back() ) );
  CHECK_THAT( 1., WithinRel( table1.total().front() ) );
  CHECK_THAT( 2., WithinRel( table1.total().back() ) );
  CHECK_THAT( 3., WithinRel( table1.elastic().front() ) );
  CHECK_THAT( 4., WithinRel( table1.elastic().back() ) );
  CHECK_THAT( 5., WithinRel( table1.fission().front() ) );
  CHECK_THAT( 6., WithinRel( table1.fission().back() ) );
  CHECK_THAT( 7., WithinRel( table1.capture().front() ) );
  CHECK_THAT( 8., WithinRel( table1.capture().back() ) );
  CHECK_THAT( 9., WithinRel( table1.heating().front() ) );
  CHECK_THAT( 10., WithinRel( table1.heating().back() ) );

  auto table2 = chunk.probabilityTable(2);
  CHECK_THAT( 1e+3, WithinRel( table2.incidentEnergy() ) );

  CHECK( 2 == table2.numberBins() );
  CHECK( 2 == table2.cumulativeProbabilities().size() );
  CHECK( 2 == table2.total().size() );
  CHECK( 2 == table2.elastic().size() );
  CHECK( 2 == table2.fission().size() );
  CHECK( 2 == table2.capture().size() );
  CHECK( 2 == table2.heating().size() );

  CHECK_THAT( 0.25, WithinRel( table2.cumulativeProbabilities().front() ) );
  CHECK_THAT( 1.0, WithinRel( table2.cumulativeProbabilities().back() ) );
  CHECK_THAT( 11., WithinRel( table2.total().front() ) );
  CHECK_THAT( 12., WithinRel( table2.total().back() ) );
  CHECK_THAT( 13., WithinRel( table2.elastic().front() ) );
  CHECK_THAT( 14., WithinRel( table2.elastic().back() ) );
  CHECK_THAT( 15., WithinRel( table2.fission().front() ) );
  CHECK_THAT( 16., WithinRel( table2.fission().back() ) );
  CHECK_THAT( 17., WithinRel( table2.capture().front() ) );
  CHECK_THAT( 18., WithinRel( table2.capture().back() ) );
  CHECK_THAT( 19., WithinRel( table2.heating().front() ) );
  CHECK_THAT( 20., WithinRel( table2.heating().back() ) );
}

ProbabilityTableBlock makeDummyBlock() {

  std::vector< ProbabilityTable > tables = {

    ProbabilityTable( 1e-3, { 0.5, 1.0 }, { 1., 2 }, { 3., 4. }, { 5., 6. },
                      { 7., 8. }, { 9., 10. } ),
    ProbabilityTable( 1e+3, { 0.25, 1.0 }, { 11., 12 }, { 13., 14. },
                      { 15., 16. }, { 17., 18. }, { 19., 20. } )
  };

  return { 1, 1, 1, 1, std::move( tables ) };
}
