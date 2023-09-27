#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/electron/PrincipalCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PrincipalCrossSectionBlock = electron::PrincipalCrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const PrincipalCrossSectionBlock& );

SCENARIO( "PrincipalCrossSectionBlock" ) {

  GIVEN( "valid data for a PrincipalCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 10., 20., 200. };
      std::vector< double > elastic = { 1., 2., 3. };
      std::vector< double > bremsstrahlung = { 4., 5., 6. };
      std::vector< double > excitation = { 7., 8., 9. };
      std::vector< std::vector< double > >
      electroionisation = { { 10., 11., 12. },
                            { 13., 14., 15. } };

      PrincipalCrossSectionBlock
      chunk( std::move( energies ), std::move( elastic ),
             std::move( bremsstrahlung ), std::move( excitation ),
             std::move( electroionisation ) );

      THEN( "a PrincipalCrossSectionBlock can be constructed and "
            "members can be tested" ) {

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

      PrincipalCrossSectionBlock chunk( xss.begin(), xss.end(), 2, 3 );

      THEN( "a PrincipalCrossSectionBlock can be constructed and "
            "members can be tested" ) {

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

  // first value of the second xs increased by 1 for testing purposes
  return {  10.,  20., 200.,
            35.,  40.,  45.,
             1.,   2.,   3.,
             4.,   5.,   6.,
             7.,   8.,   9.,
            23.,  25.,  27.,
            10.,  11.,  12.,
            13.,  14.,  15. };
}

void verifyChunk( const PrincipalCrossSectionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 24 == chunk.length() );
  CHECK( "ESZE" == chunk.name() );

  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberEnergyPoints() );
  CHECK( 2 == chunk.NSSH() );
  CHECK( 2 == chunk.numberElectronSubshells() );

  CHECK( 3 == chunk.energies().size() );
  CHECK( 3 == chunk.total().size() );
  CHECK( 3 == chunk.elastic().size() );
  CHECK( 3 == chunk.bremsstrahlung().size() );
  CHECK( 3 == chunk.excitation().size() );
  CHECK( 3 == chunk.totalElectroionisation().size() );
  CHECK( 3 == chunk.electroionisation(1).size() );
  CHECK( 3 == chunk.electroionisation(2).size() );

  CHECK(  10. == Approx( chunk.energies()[0] ) );
  CHECK(  20. == Approx( chunk.energies()[1] ) );
  CHECK( 200. == Approx( chunk.energies()[2] ) );
  CHECK(  35. == Approx( chunk.total()[0] ) );
  CHECK(  40. == Approx( chunk.total()[1] ) );
  CHECK(  45. == Approx( chunk.total()[2] ) );
  CHECK(   1. == Approx( chunk.elastic()[0] ) );
  CHECK(   2. == Approx( chunk.elastic()[1] ) );
  CHECK(   3. == Approx( chunk.elastic()[2] ) );
  CHECK(   4. == Approx( chunk.bremsstrahlung()[0] ) );
  CHECK(   5. == Approx( chunk.bremsstrahlung()[1] ) );
  CHECK(   6. == Approx( chunk.bremsstrahlung()[2] ) );
  CHECK(   7. == Approx( chunk.excitation()[0] ) );
  CHECK(   8. == Approx( chunk.excitation()[1] ) );
  CHECK(   9. == Approx( chunk.excitation()[2] ) );
  CHECK(  23. == Approx( chunk.totalElectroionisation()[0] ) );
  CHECK(  25. == Approx( chunk.totalElectroionisation()[1] ) );
  CHECK(  27. == Approx( chunk.totalElectroionisation()[2] ) );
  CHECK(  10. == Approx( chunk.electroionisation(1)[0] ) );
  CHECK(  11. == Approx( chunk.electroionisation(1)[1] ) );
  CHECK(  12. == Approx( chunk.electroionisation(1)[2] ) );
  CHECK(  13. == Approx( chunk.electroionisation(2)[0] ) );
  CHECK(  14. == Approx( chunk.electroionisation(2)[1] ) );
  CHECK(  15. == Approx( chunk.electroionisation(2)[2] ) );
}
