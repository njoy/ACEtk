#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/ProbabilityTableBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ProbabilityTableBlock = block::ProbabilityTableBlock;
using ProbabilityTable = block::ProbabilityTable;

std::vector< double > chunk();
void verifyChunk( const ProbabilityTableBlock& );

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

      ProbabilityTableBlock chunk( xss.begin(), xss.end() );

      THEN( "a ProbabilityTable can be constructed and members can "
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

  return { 2, 2, 2, -1, 0, 1, 1e-3, 1e+3,
           0.5, 1., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10.,
           0.25, 1.0, 11., 12., 13., 14., 15., 16., 17., 18., 19., 20. };
}

void verifyChunk( const ProbabilityTableBlock& chunk ) {

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
  CHECK( -1 == chunk.inelasticCompetion() );
  CHECK( 0 == chunk.IOA() );
  CHECK( 0 == chunk.absorptionCompetion() );
  CHECK( 1 == chunk.IFF() );
  CHECK( 1 == chunk.type() );

  CHECK( 2 == chunk.energies().size() );
  CHECK( 1e-3 == Approx( chunk.energies()[0] ) );
  CHECK( 1e+3 == Approx( chunk.energies()[1] ) );

  auto table1 = chunk.probabilityTable(1);
  CHECK( 1e-3 == Approx( table1.incidentEnergy() ) );

  CHECK( 2 == table1.numberBins() );
  CHECK( 2 == table1.cumulativeProbabilities().size() );
  CHECK( 2 == table1.total().size() );
  CHECK( 2 == table1.elastic().size() );
  CHECK( 2 == table1.fission().size() );
  CHECK( 2 == table1.capture().size() );
  CHECK( 2 == table1.heating().size() );

  CHECK( 0.5 == Approx( table1.cumulativeProbabilities().front() ) );
  CHECK( 1.0 == Approx( table1.cumulativeProbabilities().back() ) );
  CHECK( 1. == Approx( table1.total().front() ) );
  CHECK( 2. == Approx( table1.total().back() ) );
  CHECK( 3. == Approx( table1.elastic().front() ) );
  CHECK( 4. == Approx( table1.elastic().back() ) );
  CHECK( 5. == Approx( table1.fission().front() ) );
  CHECK( 6. == Approx( table1.fission().back() ) );
  CHECK( 7. == Approx( table1.capture().front() ) );
  CHECK( 8. == Approx( table1.capture().back() ) );
  CHECK( 9. == Approx( table1.heating().front() ) );
  CHECK( 10. == Approx( table1.heating().back() ) );

  auto table2 = chunk.probabilityTable(2);
  CHECK( 1e+3 == Approx( table2.incidentEnergy() ) );

  CHECK( 2 == table2.numberBins() );
  CHECK( 2 == table2.cumulativeProbabilities().size() );
  CHECK( 2 == table2.total().size() );
  CHECK( 2 == table2.elastic().size() );
  CHECK( 2 == table2.fission().size() );
  CHECK( 2 == table2.capture().size() );
  CHECK( 2 == table2.heating().size() );

  CHECK( 0.25 == Approx( table2.cumulativeProbabilities().front() ) );
  CHECK( 1.0 == Approx( table2.cumulativeProbabilities().back() ) );
  CHECK( 11. == Approx( table2.total().front() ) );
  CHECK( 12. == Approx( table2.total().back() ) );
  CHECK( 13. == Approx( table2.elastic().front() ) );
  CHECK( 14. == Approx( table2.elastic().back() ) );
  CHECK( 15. == Approx( table2.fission().front() ) );
  CHECK( 16. == Approx( table2.fission().back() ) );
  CHECK( 17. == Approx( table2.capture().front() ) );
  CHECK( 18. == Approx( table2.capture().back() ) );
  CHECK( 19. == Approx( table2.heating().front() ) );
  CHECK( 20. == Approx( table2.heating().back() ) );
}
