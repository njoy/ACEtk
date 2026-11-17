// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/TransitionEnergyBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EKT = electron::EKT;

std::vector< double > el_chunk();
std::vector< double > el03_chunk();
void verifyBlock( const EKT&, const std::vector< double >& );
EKT makeDummyBlock();

SCENARIO( "TransitionEnergyBlock" ) {
  
  GIVEN( "valid data for a EL format TransitionEnergyBlock instance" ) {
    
    std::vector< double > xss = el_chunk();
    
    WHEN( "the data is given explicitly" ) {
      
      EKT block( xss );
      
      THEN( "a TransitionEnergyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN( "the data is defined by iterators" ) {
      
      EKT block( xss.begin(), xss.end(), 0 );
      
      THEN( "a TransitionEnergyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN( "using the copy constructor" ) {
      
      EKT block( xss.begin(), xss.end(), 0 );
      EKT copy_block( block );
      
      THEN( "a TransitionEnergyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN( "using the move constructor" ) {
      
      EKT block( xss.begin(), xss.end(), 0 );
      EKT move_block( std::move( block ) );
      
      THEN( "a TransitionEnergyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN( "using copy assignment" ) {
      
      EKT block( xss.begin(), xss.end(), 0 );
      EKT copy_block = makeDummyBlock();
      copy_block = block;
      
      THEN( "a TransitionEnergyBlock can be copy assigned "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN( "using move assignment" ) {
      
      EKT block( xss.begin(), xss.end(), 0 );
      EKT move_block = makeDummyBlock();
      move_block = std::move( block );
      
      THEN( "a TransitionEnergyBlock can be move assigned "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
  }  // GIVEN
  
  GIVEN( "valid data for a EL03 format TransitionEnergyBlock instance" ) {
    
    std::vector< double > xss = el03_chunk();
    
    WHEN( "the data is given explicitly" ) {
      
      EKT block( xss );
      
      THEN( "a TransitionEnergyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN( "the data is defined by iterators" ) {
      
      EKT block( xss.begin(), xss.end(), 3 );
      
      THEN( "a TransitionEnergyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN( "using the copy constructor" ) {
      
      EKT block( xss.begin(), xss.end(), 3 );
      EKT copy_block( block );
      
      THEN( "a TransitionEnergyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN( "using the move constructor" ) {
      
      EKT block( xss.begin(), xss.end(), 3 );
      EKT move_block( std::move( block ) );
      
      THEN( "a TransitionEnergyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN( "using copy assignment" ) {
      
      EKT block( xss.begin(), xss.end(), 3 );
      EKT copy_block = makeDummyBlock();
      copy_block = block;
      
      THEN( "a TransitionEnergyBlock can be copy assigned "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN( "using move assignment" ) {
      
      EKT block( xss.begin(), xss.end(), 3 );
      EKT move_block = makeDummyBlock();
      move_block = std::move( block );
      
      THEN( "a TransitionEnergyBlock can be move assigned "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
  }  // GIVEN
}  // SCENARIO

std::vector< double > el_chunk() {
  
  // data from 26000.01e
  return { 7.112, 6.47, 0.9877, 0.9525 };
}

std::vector< double > el03_chunk() {
  
  // data from 26000.03e
  return { 7.112001, 6.47 };
}

void verifyBlock( const EKT& block, const std::vector< double >& xss ) {
  
  // verify xss
  auto xss_block = block.XSS();
  for ( unsigned int i = 0; i < block.length(); ++i ) {
    
    CHECK_THAT( xss[i], WithinRel( xss_block[i] ) );
  }
  
  // verify block interface
  CHECK( false == block.empty() );
  CHECK( xss.size() == block.length() );
  CHECK( "EKT" == block.name() );
  
  CHECK_THAT( xss[0], WithinRel( block.EDG() ) );
  CHECK_THAT( xss[0], WithinRel( block.kEdgeEnergy() ) );
  CHECK_THAT( xss[1], WithinRel( block.EEK() ) );
  CHECK_THAT( xss[1], WithinRel( block.kXrayEmissionEnergy() ) );
  
  if ( xss.size() > 2 ) {
    
    CHECK_THAT( xss[2],
                WithinRel( block.upperBremsstrahlungTransitionEnergy().value() ) );
    CHECK_THAT( xss[3],
                WithinRel( block.lowerBremsstrahlungTransitionEnergy().value() ) );
  } else {
    
    CHECK( std::nullopt == block.upperBremsstrahlungTransitionEnergy() );
    CHECK( std::nullopt == block.lowerBremsstrahlungTransitionEnergy() );
  }
}

EKT makeDummyBlock() {
  
  return EKT( { 1.0, 1.0 } );
}
