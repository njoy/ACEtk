// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/BremsstrahlungProductionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using XSB = electron::XSB;

std::vector< double > chunk();
void verifyBlock( const XSB&, const std::vector< double >& );
XSB makeDummyBlock();

SCENARIO( "XSB" ) {
  
  GIVEN( "valid data for a BremsstrahlungProductionBlock instance" ) {
    
    std::vector< double > xss = chunk();
    
    WHEN( "the data is given explicitly" ) {
      
      XSB block( { xss[0], xss[1], xss[2] },
                 { xss[3], xss[4], xss[5] },
                 { { xss[6], xss[7], xss[8] },
                   { xss[9], xss[10], xss[11] },
                   { xss[12], xss[13], xss[14] } } );
      
      THEN( "a BremsstrahlungProductionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "the data is defined by iterators"  ) {
      
      XSB block( xss.begin(), xss.end(), 3, 3 );
      
      THEN( "a BremsstrahlungProductionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the copy constructor" ) {
      
      XSB block( xss.begin(), xss.end(), 3, 3 );
      XSB copy_block( block );
      
      THEN( "a BremsstrahlungProductionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the move constructor" ) {
      
      XSB block( xss.begin(), xss.end(), 3, 3 );
      XSB move_block( std::move( block ) );
      
      THEN( "a BremsstrahlungProductionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using copy assignment" ) {
      
      XSB block( xss.begin(), xss.end(), 3, 3 );
      XSB copy_block = makeDummyBlock();
      copy_block = block;
      
      THEN( "a BremsstrahlungProductionBlock can be copy assigned "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using move assignment" ) {
      
      XSB block( xss.begin(), xss.end(), 3, 3 );
      XSB move_block = makeDummyBlock();
      move_block = std::move( block );
      
      THEN( "a BremsstrahlungProductionBlock can be move assigned "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
  }  // GIVEN
}  // SCENARIO

std::vector< double > chunk() {
  
  return { 0.1, 1.0, 10.0,
           0.1, 0.3, 1.0,
           0.01, 0.1, 1.0,
           0.03, 0.3, 3.0,
           0.1, 1.0, 10.0 };
}

void verifyBlock( const XSB& block, const std::vector< double >& xss ) {
  
  // verify xss
  auto xss_block = block.XSS();
  for ( unsigned int i = 0; i < block.length(); ++i ) {
    
    CHECK_THAT( xss[i], WithinRel( xss_block[i] ) );
  }
  
  // verify block interface
  CHECK( false == block.empty() );
  CHECK( xss.size() == block.length() );
  CHECK( "XSB" == block.name() );
  
  CHECK( 3 == block.NEB() );
  CHECK( 3 == block.numberElectronEnergies() );
  CHECK( 3 == block.NPB() );
  CHECK( 3 == block.numberPhotonRatios() );
  CHECK( 9 == block.numberCrossSections() );
  
  CHECK_THAT( xss[0], WithinRel( block.electronEnergy( 1 ) ) );
  CHECK_THAT( xss[0], WithinRel( block.electronEnergies()[0] ) );
  CHECK_THAT( xss[1], WithinRel( block.electronEnergy( 2 ) ) );
  CHECK_THAT( xss[1], WithinRel( block.electronEnergies()[1] ) );
  CHECK_THAT( xss[2], WithinRel( block.electronEnergy( 3 ) ) );
  CHECK_THAT( xss[2], WithinRel( block.electronEnergies()[2] ) );
  
  CHECK_THAT( xss[3], WithinRel( block.photonRatio( 1 ) ) );
  CHECK_THAT( xss[3], WithinRel( block.photonRatios()[0] ) );
  CHECK_THAT( xss[4], WithinRel( block.photonRatio( 2 ) ) );
  CHECK_THAT( xss[4], WithinRel( block.photonRatios()[1] ) );
  CHECK_THAT( xss[5], WithinRel( block.photonRatio( 3 ) ) );
  CHECK_THAT( xss[5], WithinRel( block.photonRatios()[2] ) );
  
  CHECK_THAT( xss[6], WithinRel( block.crossSection( 1, 1 ) ) );
  CHECK_THAT( xss[6], WithinRel( block.crossSections( 1 )[0] ) );
  CHECK_THAT( xss[6], WithinRel( block.crossSectionData()[0] ) );
  CHECK_THAT( xss[7], WithinRel( block.crossSection( 2, 1 ) ) );
  CHECK_THAT( xss[7], WithinRel( block.crossSections( 2 )[0] ) );
  CHECK_THAT( xss[7], WithinRel( block.crossSectionData()[1] ) );
  CHECK_THAT( xss[8], WithinRel( block.crossSection( 3, 1 ) ) );
  CHECK_THAT( xss[8], WithinRel( block.crossSections( 3 )[0] ) );
  CHECK_THAT( xss[8], WithinRel( block.crossSectionData()[2] ) );
  CHECK_THAT( xss[9], WithinRel( block.crossSection( 1, 2 ) ) );
  CHECK_THAT( xss[9], WithinRel( block.crossSections( 1 )[1] ) );
  CHECK_THAT( xss[9], WithinRel( block.crossSectionData()[3] ) );
  CHECK_THAT( xss[10], WithinRel( block.crossSection( 2, 2 ) ) );
  CHECK_THAT( xss[10], WithinRel( block.crossSections( 2 )[1] ) );
  CHECK_THAT( xss[10], WithinRel( block.crossSectionData()[4] ) );
  CHECK_THAT( xss[11], WithinRel( block.crossSection( 3, 2 ) ) );
  CHECK_THAT( xss[11], WithinRel( block.crossSections( 3 )[1] ) );
  CHECK_THAT( xss[11], WithinRel( block.crossSectionData()[5] ) );
  CHECK_THAT( xss[12], WithinRel( block.crossSection( 1, 3 ) ) );
  CHECK_THAT( xss[12], WithinRel( block.crossSections( 1 )[2] ) );
  CHECK_THAT( xss[12], WithinRel( block.crossSectionData()[6] ) );
  CHECK_THAT( xss[13], WithinRel( block.crossSection( 2, 3 ) ) );
  CHECK_THAT( xss[13], WithinRel( block.crossSections( 2 )[2] ) );
  CHECK_THAT( xss[13], WithinRel( block.crossSectionData()[7] ) );
  CHECK_THAT( xss[14], WithinRel( block.crossSection( 3, 3 ) ) );
  CHECK_THAT( xss[14], WithinRel( block.crossSections( 3 )[2] ) );
  CHECK_THAT( xss[14], WithinRel( block.crossSectionData()[8] ) );
}

XSB makeDummyBlock() {
  
  return XSB( { 1.0, 2.0 }, { 0.5, 1.0 }, { { 1.0, 2.0 }, { 3.0, 4.0 } } );
}
