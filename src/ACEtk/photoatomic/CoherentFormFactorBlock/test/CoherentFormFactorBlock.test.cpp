// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/photoatomic/CoherentFormFactorBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using CoherentFormFactorBlock = photoatomic::CoherentFormFactorBlock;

std::vector< double > chunk();
std::vector< double > chunkEprdata();
void verifyChunk( const CoherentFormFactorBlock&, const std::vector< double >& );
void verifyChunkEprdata( const CoherentFormFactorBlock&, const std::vector< double >& );
CoherentFormFactorBlock makeDummyBlock();

SCENARIO( "CoherentFormFactorBlock" ) {

  GIVEN( "valid data for a CoherentFormFactorBlock instance - mcplib style" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > integrated = {

                         0,  9.977954354245E-05,  3.964942506035E-04,  8.824146336660E-04,
        1.545120632092E-03,  2.368152245929E-03,  3.328001096461E-03,  5.572765511802E-03,
        8.114989702569E-03,  1.077179717732E-02,  1.466576582467E-02,  1.814944661202E-02,
        2.013937477439E-02,  2.411608451487E-02,  2.666620748348E-02,  2.820041294244E-02,
        2.910584927642E-02,  2.965656338431E-02,  2.998629154717E-02,  3.018996625751E-02,
        3.031651130261E-02,  3.046055891684E-02,  3.052243640030E-02,  3.055108560889E-02,
        3.056526027755E-02,  3.057267572340E-02,  3.057674989952E-02,  3.057910122834E-02,
        3.058050894259E-02,  3.058138029848E-02,  3.058193578069E-02,  3.058229824481E-02,
        3.058254088417E-02,  3.058270703249E-02,  3.058282312688E-02,  3.058297109240E-02,
        3.058304939092E-02,  3.058309313441E-02,  3.058311867888E-02,  3.058313417771E-02,
        3.058314390105E-02,  3.058315017819E-02,  3.058315433739E-02,  3.058315715668E-02,
        3.058315910726E-02,  3.058316048181E-02,  3.058316146648E-02,  3.058316218275E-02,
        3.058316271112E-02,  3.058316310589E-02,  3.058316340428E-02,  3.058316363221E-02,
        3.058316380808E-02,  3.058316394505E-02,  3.058316405266E-02
      };
      std::vector< double > factors = {

                                                                                        1,
        9.977930000000E-01,  9.912150000000E-01,  9.803950000000E-01,  9.655420000000E-01,
        9.469360000000E-01,  9.211362223597E-01,  8.688562675564E-01,  8.108240000000E-01,
        7.417575090802E-01,  6.413030000000E-01,  5.408367208541E-01,  4.807920000000E-01,
        3.497490000000E-01,  2.512750000000E-01,  1.768432017447E-01,  1.304470000000E-01,
        9.433736380317E-02,  7.059570000000E-02,  5.268096170336E-02,  4.032720000000E-02,
        2.428650000000E-02,  1.533620000000E-02,  1.009210000000E-02,  6.881610000000E-03,
        4.823560678474E-03,  3.487245440023E-03,  2.578710885266E-03,  1.943646866651E-03,
        1.493850000000E-03,  1.162827750555E-03,  9.190124274641E-04,  7.361567778277E-04,
        5.968016595264E-04,  4.890640000000E-04,  3.363261410460E-04,  2.389537358290E-04,
        1.743218160274E-04,  1.300633951738E-04,  9.902340000000E-05,  7.666272270380E-05,
        6.027975615211E-05,  4.804231924465E-05,  3.875290225804E-05,  3.160620000000E-05,
        2.602556283170E-05,  2.162488034877E-05,  1.811690042231E-05,  1.529276964899E-05,
        1.299850000000E-05,  1.111643855704E-05,  9.563173392213E-06,  8.272100115712E-06,
        7.191840373343E-06,  6.282390000000E-06
      };

      CoherentFormFactorBlock chunk( std::move( integrated ), std::move( factors ) );

      THEN( "a CoherentFormFactorBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      CoherentFormFactorBlock chunk( xss.begin(), xss.end() );

      THEN( "a CoherentFormFactorBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a CoherentFormFactorBlock instance - eprdata style" ) {

    std::vector< double > xss = chunkEprdata();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > momentum = { 0., 1., 1000., 1e+6, 1e+9 };
      std::vector< double > integrated = { 1., 2., 3., 4., 5. };
      std::vector< double > factors = { 6., 7., 8., 9., 10. };

      CoherentFormFactorBlock chunk( std::move( momentum ),
                                     std::move( integrated ),
                                     std::move( factors ) );

      THEN( "a CoherentFormFactorBlock can be constructed and members can "
            "be tested" ) {

        verifyChunkEprdata( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      CoherentFormFactorBlock chunk( xss.begin(), xss.end() );

      THEN( "a CoherentFormFactorBlock can be constructed and members can "
            "be tested" ) {

        verifyChunkEprdata( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

                     0,  9.977954354245E-05,  3.964942506035E-04,  8.824146336660E-04,
    1.545120632092E-03,  2.368152245929E-03,  3.328001096461E-03,  5.572765511802E-03,
    8.114989702569E-03,  1.077179717732E-02,  1.466576582467E-02,  1.814944661202E-02,
    2.013937477439E-02,  2.411608451487E-02,  2.666620748348E-02,  2.820041294244E-02,
    2.910584927642E-02,  2.965656338431E-02,  2.998629154717E-02,  3.018996625751E-02,
    3.031651130261E-02,  3.046055891684E-02,  3.052243640030E-02,  3.055108560889E-02,
    3.056526027755E-02,  3.057267572340E-02,  3.057674989952E-02,  3.057910122834E-02,
    3.058050894259E-02,  3.058138029848E-02,  3.058193578069E-02,  3.058229824481E-02,
    3.058254088417E-02,  3.058270703249E-02,  3.058282312688E-02,  3.058297109240E-02,
    3.058304939092E-02,  3.058309313441E-02,  3.058311867888E-02,  3.058313417771E-02,
    3.058314390105E-02,  3.058315017819E-02,  3.058315433739E-02,  3.058315715668E-02,
    3.058315910726E-02,  3.058316048181E-02,  3.058316146648E-02,  3.058316218275E-02,
    3.058316271112E-02,  3.058316310589E-02,  3.058316340428E-02,  3.058316363221E-02,
    3.058316380808E-02,  3.058316394505E-02,  3.058316405266E-02,                   1,
    9.977930000000E-01,  9.912150000000E-01,  9.803950000000E-01,  9.655420000000E-01,
    9.469360000000E-01,  9.211362223597E-01,  8.688562675564E-01,  8.108240000000E-01,
    7.417575090802E-01,  6.413030000000E-01,  5.408367208541E-01,  4.807920000000E-01,
    3.497490000000E-01,  2.512750000000E-01,  1.768432017447E-01,  1.304470000000E-01,
    9.433736380317E-02,  7.059570000000E-02,  5.268096170336E-02,  4.032720000000E-02,
    2.428650000000E-02,  1.533620000000E-02,  1.009210000000E-02,  6.881610000000E-03,
    4.823560678474E-03,  3.487245440023E-03,  2.578710885266E-03,  1.943646866651E-03,
    1.493850000000E-03,  1.162827750555E-03,  9.190124274641E-04,  7.361567778277E-04,
    5.968016595264E-04,  4.890640000000E-04,  3.363261410460E-04,  2.389537358290E-04,
    1.743218160274E-04,  1.300633951738E-04,  9.902340000000E-05,  7.666272270380E-05,
    6.027975615211E-05,  4.804231924465E-05,  3.875290225804E-05,  3.160620000000E-05,
    2.602556283170E-05,  2.162488034877E-05,  1.811690042231E-05,  1.529276964899E-05,
    1.299850000000E-05,  1.111643855704E-05,  9.563173392213E-06,  8.272100115712E-06,
    7.191840373343E-06,  6.282390000000E-06
  };
}

std::vector< double > chunkEprdata() {

  return {

    0., 1., 1000., 1e+6, 1e+9,
    1., 2., 3., 4., 5.,
    6., 7., 8., 9., 10.
  };
}

void verifyChunk( const CoherentFormFactorBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 110 == chunk.length() );
  CHECK( "JCOH" == chunk.name() );

  CHECK( 55 == chunk.NM() );
  CHECK( 55 == chunk.numberValues() );

  CHECK( 55 == chunk.momentum().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.momentum().front() ) );
  CHECK_THAT( 6.  , WithinRel( chunk.momentum().back() ) );

  CHECK( 55 == chunk.integratedFormFactors().size() );
  CHECK_THAT( 0., WithinRel( chunk.integratedFormFactors()[0] ) );
  CHECK_THAT( 3.058316405266E-02, WithinRel( chunk.integratedFormFactors().back() ) );

  CHECK( 55 == chunk.formFactors().size() );
  CHECK_THAT( 1., WithinRel( chunk.formFactors()[0] ) );
  CHECK_THAT( 6.282390000000E-06, WithinRel( chunk.formFactors().back() ) );
}

void verifyChunkEprdata( const CoherentFormFactorBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 15 == chunk.length() );
  CHECK( "JCOH" == chunk.name() );

  CHECK( 5 == chunk.NM() );
  CHECK( 5 == chunk.numberValues() );

  CHECK( 5 == chunk.momentum().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.momentum().front() ) );
  CHECK_THAT( 1e+9, WithinRel( chunk.momentum().back() ) );

  CHECK( 5 == chunk.integratedFormFactors().size() );
  CHECK_THAT( 1., WithinRel( chunk.integratedFormFactors().front() ) );
  CHECK_THAT( 5., WithinRel( chunk.integratedFormFactors().back() ) );

  CHECK( 5 == chunk.formFactors().size() );
  CHECK_THAT(  6., WithinRel( chunk.formFactors().front() ) );
  CHECK_THAT( 10., WithinRel( chunk.formFactors().back() ) );
}
