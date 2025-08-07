// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/MottScatteringCorrectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using MOT = electron::MOT;

std::vector< double > chunk();
void verifyBlock( const MOT&, const std::vector< double >& );
MOT makeDummyBlock();

SCENARIO( "MOT" ) {
  
  GIVEN( "valid data for a MottScatteringCorrectionBlock instance" ) {
    
    std::vector< double > xss = chunk();
    
    WHEN( "the data is given explicitly" ) {
      
      MOT block( { xss[0], xss[1], xss[2] },
                 { xss[3], xss[4], xss[5] },
                 { xss[6], xss[7], xss[8] },
                 { xss[9], xss[10], xss[11] },
                 { xss[12], xss[13], xss[14] },
                 { xss[15], xss[16], xss[17] } );
      
      THEN( "a MottScatteringCorrectionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "the data is defined by iterators"  ) {
      
      MOT block( xss.begin(), xss.end(), 3 );
      
      THEN( "a MottScatteringCorrectionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the copy constructor" ) {
      
      MOT block( xss.begin(), xss.end(), 3 );
      MOT copy_block( block );
      
      THEN( "a MottScatteringCorrectionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the move constructor" ) {
      
      MOT block( xss.begin(), xss.end(), 3 );
      MOT move_block( std::move( block ) );
      
      THEN( "a MottScatteringCorrectionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using copy assignment" ) {
      
      MOT block( xss.begin(), xss.end(), 3 );
      MOT copy_block = makeDummyBlock();
      copy_block = block;
      
      THEN( "a MottScatteringCorrectionBlock can be copy assigned "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using move assignment" ) {
      
      MOT block( xss.begin(), xss.end(), 3 );
      MOT move_block = makeDummyBlock();
      move_block = std::move( block );
      
      THEN( "a MottScatteringCorrectionBlock can be move assigned "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
  }  // GIVEN
}  // SCENARIO

std::vector< double > chunk() {
  
  // adapted from 26000.01e
  return { 10.0, 1.0, 0.1,
           1.0, 1.0, 1.0,
           1.03823, 1.04539, 1.06645,
           0.68123, 0.73096, 0.97863,
           0.21291, 0.31213, 0.83060,
           2.55e-3, 0.12341, 0.76169 };
}

void verifyBlock( const MOT& block, const std::vector< double >& xss ) {
  
  // verify xss
  auto xss_block = block.XSS();
  for ( unsigned int i = 0; i < block.length(); ++i ) {
    
    CHECK_THAT( xss[i], WithinRel( xss_block[i] ) );
  }
  
  // verify block interface
  CHECK( false == block.empty() );
  CHECK( xss.size() == block.length() );
  CHECK( "MOT" == block.name() );
  
  CHECK( 3 == block.NMOT() );
  CHECK( 3 == block.numberEnergyPoints() );
  
  CHECK_THAT( xss[0], WithinRel( block.energies()[0] ) );
  CHECK_THAT( xss[1], WithinRel( block.energies()[1] ) );
  CHECK_THAT( xss[2], WithinRel( block.energies()[2] ) );
  
  CHECK_THAT( xss[3], WithinRel( block.mottScatteringCorrection( 1 )[0] ) );
  CHECK_THAT( xss[4], WithinRel( block.mottScatteringCorrection( 1 )[1] ) );
  CHECK_THAT( xss[5], WithinRel( block.mottScatteringCorrection( 1 )[2] ) );
  
  CHECK_THAT( xss[6], WithinRel( block.mottScatteringCorrection( 2 )[0] ) );
  CHECK_THAT( xss[7], WithinRel( block.mottScatteringCorrection( 2 )[1] ) );
  CHECK_THAT( xss[8], WithinRel( block.mottScatteringCorrection( 2 )[2] ) );
  
  CHECK_THAT( xss[9], WithinRel( block.mottScatteringCorrection( 3 )[0] ) );
  CHECK_THAT( xss[10], WithinRel( block.mottScatteringCorrection( 3 )[1] ) );
  CHECK_THAT( xss[11], WithinRel( block.mottScatteringCorrection( 3 )[2] ) );
  
  CHECK_THAT( xss[12], WithinRel( block.mottScatteringCorrection( 4 )[0] ) );
  CHECK_THAT( xss[13], WithinRel( block.mottScatteringCorrection( 4 )[1] ) );
  CHECK_THAT( xss[14], WithinRel( block.mottScatteringCorrection( 4 )[2] ) );
  
  CHECK_THAT( xss[15], WithinRel( block.mottScatteringCorrection( 5 )[0] ) );
  CHECK_THAT( xss[16], WithinRel( block.mottScatteringCorrection( 5 )[1] ) );
  CHECK_THAT( xss[17], WithinRel( block.mottScatteringCorrection( 5 )[2] ) );
}

MOT makeDummyBlock() {
  
  return MOT( { 1.0 }, { 2.0 }, { 3.0 }, { 4.0 }, { 5.0 }, { 6.0 } );
}
