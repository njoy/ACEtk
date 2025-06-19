// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/ProbabilityTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ProbabilityTable = continuous::ProbabilityTable;

std::vector< double > chunk();
void verifyChunk( const ProbabilityTable&, const std::vector< double >& );
ProbabilityTable makeDummyBlock();

SCENARIO( "ProbabilityTable" ) {

  GIVEN( "valid data for a ProbabilityTable instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double incident = 2.250001e-3;
      std::vector< double > probabilities = {

                             2.97187500000E-03,   5.33593800000E-03,   1.41937500000E-02,
        4.30500000000E-02,   1.15618800000E-01,   2.73403200000E-01,   4.29101600000E-01,
        5.67407900000E-01,   6.83036000000E-01,   7.97178200000E-01,   9.04947000000E-01,
        9.64268800000E-01,   9.85792300000E-01,   9.95418800000E-01,   9.98034500000E-01,
        1.00000000000E+00
      };
      std::vector< double > total = {

                             6.20303500000E-01,   6.42335400000E-01,   6.60452300000E-01,
        6.90002000000E-01,   7.33742600000E-01,   7.99614200000E-01,   8.76401300000E-01,
        9.51171000000E-01,   1.02867900000E+00,   1.12121100000E+00,   1.24689400000E+00,
        1.40225100000E+00,   1.55842900000E+00,   1.71112000000E+00,   1.86097600000E+00,
        2.08166900000E+00
      };
      std::vector< double > elastic = {

                             8.88269000000E-01,   9.12816500000E-01,   9.23308400000E-01,
        9.37411100000E-01,   9.49310700000E-01,   9.61475400000E-01,   9.73965600000E-01,
        9.85856900000E-01,   9.99825000000E-01,   1.01810900000E+00,   1.05061900000E+00,
        1.09372600000E+00,   1.13727700000E+00,   1.17577200000E+00,   1.21880600000E+00,
        1.25902700000E+00
      };
      std::vector< double > fission = {

                             2.06017200000E-01,   2.23310300000E-01,   2.54194800000E-01,
        3.08081500000E-01,   4.02651200000E-01,   5.53739000000E-01,   7.31365600000E-01,
        9.03602600000E-01,   1.07779300000E+00,   1.28805300000E+00,   1.55582400000E+00,
        1.84830500000E+00,   2.13848200000E+00,   2.46773600000E+00,   2.73598100000E+00,
        3.24694300000E+00
      };
      std::vector< double > capture = {

                             1.79948200000E-01,   2.00216700000E-01,   2.28134200000E-01,
        2.81797100000E-01,   3.73393600000E-01,   5.21435100000E-01,   6.99884000000E-01,
        8.77272600000E-01,   1.06353100000E+00,   1.26987600000E+00,   1.55414500000E+00,
        1.99555900000E+00,   2.44876200000E+00,   2.78909800000E+00,   3.24494800000E+00,
        3.73081700000E+00
      };
      std::vector< double > heating = {

                             1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,
        1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,
        1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,
        1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,
        1.00000000000E+00
      };

      ProbabilityTable chunk( incident,
                              std::move( probabilities ),
                              std::move( total ),
                              std::move( elastic ),
                              std::move( fission ),
                              std::move( capture ),
                              std::move( heating ) );

      THEN( "a ProbabilityTable can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      ProbabilityTable chunk( xss.begin(), xss.end(), 2.250001e-3, 16 );

      THEN( "a ProbabilityTable can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      ProbabilityTable chunk( xss.begin(), xss.end(), 2.250001e-3, 16 );
      ProbabilityTable copy( chunk );

      THEN( "an ProbabilityTable can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      ProbabilityTable chunk( xss.begin(), xss.end(), 2.250001e-3, 16 );
      ProbabilityTable move( std::move( chunk ) );

      THEN( "an ProbabilityTable can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      ProbabilityTable chunk( xss.begin(), xss.end(), 2.250001e-3, 16 );
      ProbabilityTable copy = makeDummyBlock();
      copy = chunk;

      THEN( "an ProbabilityTable can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      ProbabilityTable chunk( xss.begin(), xss.end(), 2.250001e-3, 16 );
      ProbabilityTable move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an ProbabilityTable can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

                         2.97187500000E-03,   5.33593800000E-03,   1.41937500000E-02,
    4.30500000000E-02,   1.15618800000E-01,   2.73403200000E-01,   4.29101600000E-01,
    5.67407900000E-01,   6.83036000000E-01,   7.97178200000E-01,   9.04947000000E-01,
    9.64268800000E-01,   9.85792300000E-01,   9.95418800000E-01,   9.98034500000E-01,
    1.00000000000E+00,   6.20303500000E-01,   6.42335400000E-01,   6.60452300000E-01,
    6.90002000000E-01,   7.33742600000E-01,   7.99614200000E-01,   8.76401300000E-01,
    9.51171000000E-01,   1.02867900000E+00,   1.12121100000E+00,   1.24689400000E+00,
    1.40225100000E+00,   1.55842900000E+00,   1.71112000000E+00,   1.86097600000E+00,
    2.08166900000E+00,   8.88269000000E-01,   9.12816500000E-01,   9.23308400000E-01,
    9.37411100000E-01,   9.49310700000E-01,   9.61475400000E-01,   9.73965600000E-01,
    9.85856900000E-01,   9.99825000000E-01,   1.01810900000E+00,   1.05061900000E+00,
    1.09372600000E+00,   1.13727700000E+00,   1.17577200000E+00,   1.21880600000E+00,
    1.25902700000E+00,   2.06017200000E-01,   2.23310300000E-01,   2.54194800000E-01,
    3.08081500000E-01,   4.02651200000E-01,   5.53739000000E-01,   7.31365600000E-01,
    9.03602600000E-01,   1.07779300000E+00,   1.28805300000E+00,   1.55582400000E+00,
    1.84830500000E+00,   2.13848200000E+00,   2.46773600000E+00,   2.73598100000E+00,
    3.24694300000E+00,   1.79948200000E-01,   2.00216700000E-01,   2.28134200000E-01,
    2.81797100000E-01,   3.73393600000E-01,   5.21435100000E-01,   6.99884000000E-01,
    8.77272600000E-01,   1.06353100000E+00,   1.26987600000E+00,   1.55414500000E+00,
    1.99555900000E+00,   2.44876200000E+00,   2.78909800000E+00,   3.24494800000E+00,
    3.73081700000E+00,   1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,
    1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,
    1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,
    1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,
    1.00000000000E+00
  };
}

void verifyChunk( const ProbabilityTable& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 96 == chunk.length() );
  CHECK( "ProbabilityTable" == chunk.name() );

  CHECK( 96 == chunk.XSS().size() );

  CHECK_THAT( 2.250001e-3, WithinRel( chunk.incidentEnergy() ) );

  CHECK( 16 == chunk.numberBins() );
  CHECK( 16 == chunk.cumulativeProbabilities().size() );
  CHECK( 16 == chunk.total().size() );
  CHECK( 16 == chunk.elastic().size() );
  CHECK( 16 == chunk.fission().size() );
  CHECK( 16 == chunk.capture().size() );
  CHECK( 16 == chunk.heating().size() );

  CHECK_THAT( 2.97187500000E-03, WithinRel( chunk.cumulativeProbabilities().front() ) );
  CHECK_THAT( 1., WithinRel( chunk.cumulativeProbabilities().back() ) );
  CHECK_THAT( 6.20303500000E-01, WithinRel( chunk.total().front() ) );
  CHECK_THAT( 2.08166900000E+00, WithinRel( chunk.total().back() ) );
  CHECK_THAT( 8.88269000000E-01, WithinRel( chunk.elastic().front() ) );
  CHECK_THAT( 1.25902700000E+00, WithinRel( chunk.elastic().back() ) );
  CHECK_THAT( 2.06017200000E-01, WithinRel( chunk.fission().front() ) );
  CHECK_THAT( 3.24694300000E+00, WithinRel( chunk.fission().back() ) );
  CHECK_THAT( 1.79948200000E-01, WithinRel( chunk.capture().front() ) );
  CHECK_THAT( 3.73081700000E+00, WithinRel( chunk.capture().back() ) );
  CHECK_THAT( 1., WithinRel( chunk.heating().front() ) );
  CHECK_THAT( 1., WithinRel( chunk.heating().back() ) );
}

ProbabilityTable makeDummyBlock() {

  return { 1., { 1., 2. }, { 3., 4. }, { 5., 6. },
               { 1., 2. }, { 3., 4. }, { 5., 6. } };
}
