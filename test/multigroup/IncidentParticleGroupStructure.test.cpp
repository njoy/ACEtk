// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/IncidentParticleGroupStructureBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using IncidentParticleGroupStructureBlock = multigroup::IncidentParticleGroupStructureBlock;

std::vector< double > chunk();
void verifyChunk( const IncidentParticleGroupStructureBlock&, const std::vector< double >& );

SCENARIO( "IncidentParticleGroupStructureBlock" ) {

  GIVEN( "valid data for a IncidentParticleGroupStructureBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > centers = {

           1.6000E+01,  1.42500E+01,  1.2750E+01,  1.1000E+01,
           8.8950E+00,  6.93000E+00,  4.8750E+00,  3.2725E+00,
           2.5485E+00,  1.98500E+00,  1.5455E+00,  1.0880E+00,
           6.6150E-01,  4.01500E-01,  2.4350E-01,  1.2580E-01,
           4.6200E-02,  1.69600E-02,  6.2350E-03,  2.2925E-03,
           8.4450E-04,  3.10500E-04,  1.1420E-04,  4.2000E-05,
           1.5460E-05,  5.69000E-06,  2.0950E-06,  7.7200E-07,
           2.8300E-07,  7.60695E-08,
      };
      
      std::vector< double > widths = {

          2.000E+00,  1.500E+00,
          1.500E+00,  2.000E+00,  2.210E+00,  1.72000E+00,
          2.390E+00,  8.150E-01,  6.330E-01,  4.94000E-01,
          3.850E-01,  5.300E-01,  3.230E-01,  1.97000E-01,
          1.190E-01,  1.164E-01,  4.280E-02,  1.56800E-02,
          5.770E-03,  2.115E-03,  7.810E-04,  2.87000E-04,
          1.056E-04,  3.880E-05,  1.428E-05,  5.26000E-06,
          1.930E-06,  7.160E-07,  2.620E-07,  1.51861E-07,
      };

      IncidentParticleGroupStructureBlock chunk( std::move( centers ),
                                        std::move( widths ));

      THEN( "a IncidentParticleGroupStructureBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      IncidentParticleGroupStructureBlock chunk( xss.begin(), xss.end(), 30 );

      THEN( "a IncidentParticleGroupStructureBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      IncidentParticleGroupStructureBlock chunk( xss.begin(), xss.end(), 30 );
      IncidentParticleGroupStructureBlock copy( chunk );

      THEN( "an IncidentParticleGroupStructureBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      IncidentParticleGroupStructureBlock chunk( xss.begin(), xss.end(), 30 );
      IncidentParticleGroupStructureBlock move( std::move( chunk ) );

      THEN( "an IncidentParticleGroupStructureBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

                  16,  1.425000000000E+01,  1.275000000000E+01,                  11,
  8.895000000000E+00,  6.930000000000E+00,  4.875000000000E+00,  3.272500000000E+00,
  2.548500000000E+00,  1.985000000000E+00,  1.545500000000E+00,  1.088000000000E+00,
  6.615000000000E-01,  4.015000000000E-01,  2.435000000000E-01,  1.258000000000E-01,
  4.620000000000E-02,  1.696000000000E-02,  6.235000000000E-03,  2.292500000000E-03,
  8.445000000000E-04,  3.105000000000E-04,  1.142000000000E-04,  4.200000000000E-05,
  1.546000000000E-05,  5.690000000000E-06,  2.095000000000E-06,  7.720000000000E-07,
  2.830000000000E-07,  7.606950000000E-08,                   2,  1.500000000000E+00,
  1.500000000000E+00,                   2,  2.210000000000E+00,  1.720000000000E+00,
  2.390000000000E+00,  8.150000000000E-01,  6.330000000000E-01,  4.940000000000E-01,
  3.850000000000E-01,  5.300000000000E-01,  3.230000000000E-01,  1.970000000000E-01,
  1.190000000000E-01,  1.164000000000E-01,  4.280000000000E-02,  1.568000000000E-02,
  5.770000000000E-03,  2.115000000000E-03,  7.810000000000E-04,  2.870000000000E-04,
  1.056000000000E-04,  3.880000000000E-05,  1.428000000000E-05,  5.260000000000E-06,
  1.930000000000E-06,  7.160000000000E-07,  2.620000000000E-07,  1.518610000000E-07,
  };
}

void verifyChunk( const IncidentParticleGroupStructureBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 30*2 == chunk.length() );
  CHECK( "ERG" == chunk.name() );

  CHECK( 30*2 == chunk.XSS().size() );

  CHECK( 30 == chunk.NGRP() );
  CHECK( 30 == chunk.numberEnergyGroups() );
  CHECK( 30 == chunk.groupCenters().size() );
  CHECK( 30 == chunk.groupWidths().size() );

  CHECK_THAT( 16, WithinRel( chunk.groupCenters().front() ) );
  CHECK_THAT( 7.60695E-08, WithinRel( chunk.groupCenters().back() ) );
  CHECK_THAT( 2, WithinRel( chunk.groupWidths().front() ) );
  CHECK_THAT( 1.51861E-07, WithinRel( chunk.groupWidths().back() ) );
}
