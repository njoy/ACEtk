// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/ElectronTable.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::ACEtk;

void verifyTableEl( const ElectronTable& );
void verifyTableEl03( const ElectronTable& );

SCENARIO( "ElectronTable" ) {
  
  GIVEN( "valid data for an ElectronTable - el format" ) {
    
    WHEN( "constructing an ElectronTable from a Table" ) {
      
      auto table_to_move = fromFile( "26000.01e" );
      ElectronTable table( std::move( table_to_move ) );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the copy constructor" ) {
      
      ElectronTable table_to_copy( fromFile( "26000.01e" ) );
      ElectronTable table( table_to_copy );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the move constructor" ) {
      
      ElectronTable table_to_move( fromFile( "26000.01e" ) );
      ElectronTable table( std::move( table_to_move ) );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the copy assignment" ) {
      
      ElectronTable table_to_copy( fromFile( "26000.01e" ) );
      ElectronTable table( fromFile( "6000.03e" ) );
      table = table_to_copy;
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the move assignment" ) {
      
      ElectronTable table_to_move( fromFile( "26000.01e" ) );
      ElectronTable table( fromFile( "6000.03e" ) );
      table = std::move( table_to_move );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable from its components" ) {
      
      ElectronTable base_table( fromFile( "26000.01e" ) );
      ElectronTable table( 26, base_table.header(),
                           { 26054, 26056, 26057, 26058 },
                           { 53.476242, 55.454429, 56.446290, 57.435600 },
                           base_table.EKT(), base_table.RAD(),
                           base_table.MOT(), base_table.RLY(),
                           base_table.XSB(), base_table.CRB(),
                           base_table.HFB(), base_table.RKT(),
                           base_table.RKA(), base_table.OSC() );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
  }  // GIVEN
  
  GIVEN( "valid data for an ElectronTable - el03 format" ) {
    
    WHEN( "constructing an ElectronTable from a Table" ) {
      
      auto table_to_move = fromFile( "6000.03e" );
      ElectronTable table( std::move( table_to_move ) );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the copy constructor" ) {
      
      ElectronTable table_to_copy( fromFile( "6000.03e" ) );
      ElectronTable table( table_to_copy );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the move constructor" ) {
      
      ElectronTable table_to_move( fromFile( "6000.03e" ) );
      ElectronTable table( std::move( table_to_move ) );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the copy assignment" ) {
      
      ElectronTable table_to_copy( fromFile( "6000.03e" ) );
      ElectronTable table( fromFile( "6000.03e" ) );
      table = table_to_copy;
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the move assignment" ) {
      
      ElectronTable table_to_move( fromFile( "6000.03e" ) );
      ElectronTable table( fromFile( "26000.01e" ) );
      table = std::move( table_to_move );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable from its components" ) {
      
      ElectronTable base_table( fromFile( "6000.03e" ) );
      njoy::tools::Log::info( "Base table type: {}", base_table.NEL() );
      ElectronTable table( 6, base_table.header(),
                           { 6012, 6013 },
                           { 11.896914, 12.891649 },
                           base_table.EKT(), base_table.RAD(),
                           base_table.MOT(), base_table.RLY(),
                           base_table.XSB(), base_table.CRB(),
                           base_table.HFB(), base_table.RKT(),
                           base_table.RKA(), base_table.OSC() );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
  }  // GIVEN
}  // SCENARIO

void verifyTableEl( const ElectronTable& table ) {
  
  // verify table type
  CHECK( 3 != table.NEL() );
  CHECK( 3 != table.electronDataFormat() );
}

void verifyTableEl03( const ElectronTable& table ) {
  
  // verify table type
  CHECK( 3 == table.NEL() );
  CHECK( 3 == table.electronDataFormat() );
}
