// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/photoatomic/ComptonProfileBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ComptonProfileBlock = photoatomic::ComptonProfileBlock;
using ComptonProfile = photoatomic::ComptonProfile;

std::vector< double > chunk();
void verifyChunk( const ComptonProfileBlock&, const std::vector< double >& );
ComptonProfileBlock makeDummyBlock();

SCENARIO( "ComptonProfileBlock" ) {

  GIVEN( "valid data for a ComptonProfileBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< ComptonProfile > profiles = {

        ComptonProfile(
          2,
          {                      0.000000000000e+00,  5.000000000000e-02,  1.000000000000e-01,
            1.500000000000e-01,  2.000000000000e-01,  3.000000000000e-01,  4.000000000000e-01,
            5.000000000000e-01,  6.000000000000e-01,  7.000000000000e-01,  8.000000000000e-01,
            1.000000000000e+00,  1.200000000000e+00,  1.400000000000e+00,  1.600000000000e+00,
            1.800000000000e+00,  2.000000000000e+00,  2.400000000000e+00,  3.000000000000e+00,
            4.000000000000e+00,  5.000000000000e+00,  6.000000000000e+00,  7.000000000000e+00,
            8.000000000000e+00,  1.000000000000e+01,  1.500000000000e+01,  2.000000000000e+01,
            3.000000000000e+01,  4.000000000000e+01,  6.000000000000e+01,  1.000000000000e+02 },
          { 6.527863344596e-01,  6.508021814673e-01,  6.488180284750e-01,  6.448497224905e-01,
            6.388972635137e-01,  6.250081925677e-01,  6.051666626449e-01,  5.813568267376e-01,
            5.535786848457e-01,  5.218322369692e-01,  4.900857890928e-01,  4.226245873553e-01,
            3.571475386101e-01,  2.956387958495e-01,  2.420666650580e-01,  1.964311462356e-01,
            1.583354087838e-01,  1.017870485039e-01,  5.277846959461e-02,  1.871056271719e-02,
            7.361207601353e-03,  3.194486317568e-03,  1.515892886101e-03,  7.718355139963e-04,
            2.380983590734e-04,  2.380983590734e-05,  4.761967181468e-06,  4.365136583013e-07,
            7.738196669886e-08,  6.944535472975e-09,  3.571475386101e-10 },
          {                                                                0.000000000000e+00,
            3.258971289817e-02,  6.508021814673e-02,  9.742191192087e-02,  1.295155865710e-01,
            1.927108593750e-01,  2.542196021357e-01,  3.135457766048e-01,  3.702925521840e-01,
            4.240630982747e-01,  4.746589995778e-01,  5.659300372226e-01,  6.439072498192e-01,
            7.091858832651e-01,  7.629564293559e-01,  8.068062104852e-01,  8.422828659872e-01,
            8.943073574447e-01,  9.406770128742e-01,  9.764215290301e-01,  9.894574141894e-01,
            9.947352611489e-01,  9.970904507507e-01,  9.982343149508e-01,  9.992442488238e-01,
            9.998990193113e-01,  9.999704488190e-01,  9.999964412232e-01,  9.999990107013e-01,
            9.999998539663e-01,  1.000000000000e+00 } ),
        ComptonProfile(
          2,
          { 0.000000000000e+00,  5.000000000000e-02,  1.000000000000e-01,  1.500000000000e-01,
            2.000000000000e-01,  3.000000000000e-01,  4.000000000000e-01,  5.000000000000e-01,
            6.000000000000e-01,  7.000000000000e-01,  8.000000000000e-01,  1.000000000000e+00,
            1.200000000000e+00,  1.400000000000e+00,  1.600000000000e+00,  1.800000000000e+00,
            2.000000000000e+00,  2.400000000000e+00,  3.000000000000e+00,  4.000000000000e+00,
            5.000000000000e+00,  6.000000000000e+00,  7.000000000000e+00,  8.000000000000e+00,
            1.000000000000e+01,  1.500000000000e+01,  2.000000000000e+01,  3.000000000000e+01,
            4.000000000000e+01,  6.000000000000e+01,  1.000000000000e+02 },
          {                                                                3.848272047027e+00,
            3.709416870073e+00,  3.352360700761e+00,  2.836612900644e+00,  2.261355738975e+00,
            1.213990975660e+00,  5.435188355080e-01,  2.142337015871e-01,  8.152782532619e-02,
            3.848272047027e-02,  2.796939992942e-02,  2.658084815988e-02,  2.380374462079e-02,
            1.900332278893e-02,  1.436159258787e-02,  1.063233926395e-02,  7.835399271009e-03,
            4.324346939443e-03,  1.908266860433e-03,  5.851753885943e-04,  2.142337015871e-04,
            8.886731325094e-05,  4.086309493235e-05,  2.043154746618e-05,  6.149300693703e-06,
            6.149300693703e-07,  1.170350777189e-07,  1.071168507935e-08,  1.904299569663e-09,
            1.705935031156e-10,  8.728039694288e-12 },
          {                                           0.000000000000e+00,  1.889422229275e-01,
            3.654866621983e-01,  5.202110022334e-01,  6.476602182239e-01,  8.214275539556e-01,
            9.093030445140e-01,  9.471906713688e-01,  9.619787477145e-01,  9.679792750043e-01,
            9.713018810243e-01,  9.767569058332e-01,  9.817953651113e-01,  9.860760718522e-01,
            9.894125633899e-01,  9.919119565751e-01,  9.937587304286e-01,  9.961906796707e-01,
            9.980604638107e-01,  9.993071849352e-01,  9.997068894803e-01,  9.998584399877e-01,
            9.999233051918e-01,  9.999539525130e-01,  9.999805333611e-01,  9.999974439380e-01,
            9.999992738509e-01,  9.999999125847e-01,  9.999999756646e-01,  9.999999964136e-01,
            1.000000000000e+00 } ) };

      ComptonProfileBlock chunk( std::move( profiles ) );

      THEN( "a ComptonProfileBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      ComptonProfileBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );

      THEN( "a ComptonProfileBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      ComptonProfileBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );
      ComptonProfileBlock copy( chunk );

      THEN( "an ComptonProfileBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      ComptonProfileBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );
      ComptonProfileBlock move( std::move( chunk ) );

      THEN( "an ComptonProfileBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      ComptonProfileBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );
      ComptonProfileBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an ComptonProfileBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      ComptonProfileBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );
      ComptonProfileBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an ComptonProfileBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  // first value of the second xs increased by 1 for testing purposes
  return {

                                          1,                  96,                   2,
                    31,  0.000000000000e+00,  5.000000000000e-02,  1.000000000000e-01,
    1.500000000000e-01,  2.000000000000e-01,  3.000000000000e-01,  4.000000000000e-01,
    5.000000000000e-01,  6.000000000000e-01,  7.000000000000e-01,  8.000000000000e-01,
    1.000000000000e+00,  1.200000000000e+00,  1.400000000000e+00,  1.600000000000e+00,
    1.800000000000e+00,  2.000000000000e+00,  2.400000000000e+00,  3.000000000000e+00,
    4.000000000000e+00,  5.000000000000e+00,  6.000000000000e+00,  7.000000000000e+00,
    8.000000000000e+00,  1.000000000000e+01,  1.500000000000e+01,  2.000000000000e+01,
    3.000000000000e+01,  4.000000000000e+01,  6.000000000000e+01,  1.000000000000e+02,
    6.527863344596e-01,  6.508021814673e-01,  6.488180284750e-01,  6.448497224905e-01,
    6.388972635137e-01,  6.250081925677e-01,  6.051666626449e-01,  5.813568267376e-01,
    5.535786848457e-01,  5.218322369692e-01,  4.900857890928e-01,  4.226245873553e-01,
    3.571475386101e-01,  2.956387958495e-01,  2.420666650580e-01,  1.964311462356e-01,
    1.583354087838e-01,  1.017870485039e-01,  5.277846959461e-02,  1.871056271719e-02,
    7.361207601353e-03,  3.194486317568e-03,  1.515892886101e-03,  7.718355139963e-04,
    2.380983590734e-04,  2.380983590734e-05,  4.761967181468e-06,  4.365136583013e-07,
    7.738196669886e-08,  6.944535472975e-09,  3.571475386101e-10,  0.000000000000e+00,
    3.258971289817e-02,  6.508021814673e-02,  9.742191192087e-02,  1.295155865710e-01,
    1.927108593750e-01,  2.542196021357e-01,  3.135457766048e-01,  3.702925521840e-01,
    4.240630982747e-01,  4.746589995778e-01,  5.659300372226e-01,  6.439072498192e-01,
    7.091858832651e-01,  7.629564293559e-01,  8.068062104852e-01,  8.422828659872e-01,
    8.943073574447e-01,  9.406770128742e-01,  9.764215290301e-01,  9.894574141894e-01,
    9.947352611489e-01,  9.970904507507e-01,  9.982343149508e-01,  9.992442488238e-01,
    9.998990193113e-01,  9.999704488190e-01,  9.999964412232e-01,  9.999990107013e-01,
    9.999998539663e-01,  1.000000000000e+00,                   2,                  31,
    0.000000000000e+00,  5.000000000000e-02,  1.000000000000e-01,  1.500000000000e-01,
    2.000000000000e-01,  3.000000000000e-01,  4.000000000000e-01,  5.000000000000e-01,
    6.000000000000e-01,  7.000000000000e-01,  8.000000000000e-01,  1.000000000000e+00,
    1.200000000000e+00,  1.400000000000e+00,  1.600000000000e+00,  1.800000000000e+00,
    2.000000000000e+00,  2.400000000000e+00,  3.000000000000e+00,  4.000000000000e+00,
    5.000000000000e+00,  6.000000000000e+00,  7.000000000000e+00,  8.000000000000e+00,
    1.000000000000e+01,  1.500000000000e+01,  2.000000000000e+01,  3.000000000000e+01,
    4.000000000000e+01,  6.000000000000e+01,  1.000000000000e+02,  3.848272047027e+00,
    3.709416870073e+00,  3.352360700761e+00,  2.836612900644e+00,  2.261355738975e+00,
    1.213990975660e+00,  5.435188355080e-01,  2.142337015871e-01,  8.152782532619e-02,
    3.848272047027e-02,  2.796939992942e-02,  2.658084815988e-02,  2.380374462079e-02,
    1.900332278893e-02,  1.436159258787e-02,  1.063233926395e-02,  7.835399271009e-03,
    4.324346939443e-03,  1.908266860433e-03,  5.851753885943e-04,  2.142337015871e-04,
    8.886731325094e-05,  4.086309493235e-05,  2.043154746618e-05,  6.149300693703e-06,
    6.149300693703e-07,  1.170350777189e-07,  1.071168507935e-08,  1.904299569663e-09,
    1.705935031156e-10,  8.728039694288e-12,  0.000000000000e+00,  1.889422229275e-01,
    3.654866621983e-01,  5.202110022334e-01,  6.476602182239e-01,  8.214275539556e-01,
    9.093030445140e-01,  9.471906713688e-01,  9.619787477145e-01,  9.679792750043e-01,
    9.713018810243e-01,  9.767569058332e-01,  9.817953651113e-01,  9.860760718522e-01,
    9.894125633899e-01,  9.919119565751e-01,  9.937587304286e-01,  9.961906796707e-01,
    9.980604638107e-01,  9.993071849352e-01,  9.997068894803e-01,  9.998584399877e-01,
    9.999233051918e-01,  9.999539525130e-01,  9.999805333611e-01,  9.999974439380e-01,
    9.999992738509e-01,  9.999999125847e-01,  9.999999756646e-01,  9.999999964136e-01,
    1.000000000000e+00 };
}

void verifyChunk( const ComptonProfileBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 192 == chunk.length() );
  CHECK( "SWD" == chunk.name() );

  CHECK( 2 == chunk.NSH() );
  CHECK( 2 == chunk.numberElectronShells() );
  CHECK( 2 == chunk.data().size() );

  CHECK( 1 == chunk.LSWD(1) );
  CHECK( 96 == chunk.LSWD(2) );
  CHECK( 1 == chunk.comptonProfileLocator(1) );
  CHECK( 96 == chunk.comptonProfileLocator(2) );

  auto profile = chunk.comptonProfile(1);
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK_THAT( 0., WithinRel( profile.momentum().front() ) );
  CHECK_THAT( 100., WithinRel( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK_THAT( 6.527863344596e-01, WithinRel( profile.pdf().front() ) );
  CHECK_THAT( 3.571475386101e-10, WithinRel( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK_THAT( 0., WithinRel( profile.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( profile.cdf().back() ) );

  profile = chunk.comptonProfile(2);
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK_THAT( 0., WithinRel( profile.momentum().front() ) );
  CHECK_THAT( 100., WithinRel( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK_THAT( 3.848272047027e+00, WithinRel( profile.pdf().front() ) );
  CHECK_THAT( 8.728039694288e-12, WithinRel( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK_THAT( 0., WithinRel( profile.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( profile.cdf().back() ) );

  profile = chunk.data()[0];
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK_THAT( 0., WithinRel( profile.momentum().front() ) );
  CHECK_THAT( 100., WithinRel( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK_THAT( 6.527863344596e-01, WithinRel( profile.pdf().front() ) );
  CHECK_THAT( 3.571475386101e-10, WithinRel( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK_THAT( 0., WithinRel( profile.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( profile.cdf().back() ) );

  profile = chunk.data()[1];
  CHECK( 2 == profile.interpolation() );
  CHECK( 31 == profile.numberValues() );
  CHECK( 31 == profile.momentum().size() );
  CHECK_THAT( 0., WithinRel( profile.momentum().front() ) );
  CHECK_THAT( 100., WithinRel( profile.momentum().back() ) );
  CHECK( 31 == profile.pdf().size() );
  CHECK_THAT( 3.848272047027e+00, WithinRel( profile.pdf().front() ) );
  CHECK_THAT( 8.728039694288e-12, WithinRel( profile.pdf().back() ) );
  CHECK( 31 == profile.cdf().size() );
  CHECK_THAT( 0., WithinRel( profile.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( profile.cdf().back() ) );
}

ComptonProfileBlock makeDummyBlock() {

  return { { { 2, { 1., 2. }, { 3., 4. }, { 5., 6. } } } };
}
