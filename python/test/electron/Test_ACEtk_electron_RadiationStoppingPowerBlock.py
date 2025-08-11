# standard imports
import unittest

# third party imports

# local imports
from ACEtk.electron import RadiationStoppingPowerBlock

class Test_ACEtk_electron_RadiationStoppingPowerBlock( unittest.TestCase ) :
    """Unit tests for the RadiationStoppingPowerBlock class."""
    
    chunk_el = [ 0.1, 1.0, 10.0, 0.2, 1.2, 3.0 ]
    chunk_el03 = [ 0.1, 1.0, 10.0, 0.2, 1.2, 3.0, 1.05, 1.15, 1.02 ]
    
    def test_component_el( self ):
        """Unit test for the RadiationStoppingPowerBlock in the el format."""
        
        def verify_block( self, block ) :
            
            # verify content
            self.assertEqual( False, block.empty )
            self.assertEqual( 6, block.length )
            self.assertEqual( "RAD", block.name )
            
            self.assertEqual( 3, block.NRAD )
            self.assertEqual( 3, block.number_energy_points )
            
            self.assertAlmostEqual( self.chunk_el[0],
                                    block.energies[0] )
            self.assertAlmostEqual( self.chunk_el[1],
                                    block.energies[1] )
            self.assertAlmostEqual( self.chunk_el[2],
                                    block.energies[2] )
            self.assertAlmostEqual( self.chunk_el[3],
                                    block.stopping_powers[0] )
            self.assertAlmostEqual( self.chunk_el[4],
                                    block.stopping_powers[1] )
            self.assertAlmostEqual( self.chunk_el[5],
                                    block.stopping_powers[2] )
            self.assertIsNone( block.corrections )
            
            # verify the xss array
            self.assertEqual( 6, len( block.xss_array ) )
            for index in range( block.length ):
                
                self.assertAlmostEqual( self.chunk_el[index],
                                        block.xss_array[index] )
            
        # the data is given explicitly
        block = RadiationStoppingPowerBlock( self.chunk_el[0:3],
                                             self.chunk_el[3:6] )
        
        verify_block( self, block )
    
    def test_component_el03( self ):
        """Unit test for the RadiationStoppingPowerBlock in the el03 format."""
        
        def verify_block( self, block ) :
            
            # verify content
            self.assertEqual( False, block.empty )
            self.assertEqual( 9, block.length )
            self.assertEqual( "RAD", block.name )
            
            self.assertEqual( 3, block.NRAD )
            self.assertEqual( 3, block.number_energy_points )
            
            self.assertAlmostEqual( self.chunk_el03[0],
                                    block.energies[0] )
            self.assertAlmostEqual( self.chunk_el03[1],
                                    block.energies[1] )
            self.assertAlmostEqual( self.chunk_el03[2],
                                    block.energies[2] )
            self.assertAlmostEqual( self.chunk_el03[3],
                                    block.stopping_powers[0] )
            self.assertAlmostEqual( self.chunk_el03[4],
                                    block.stopping_powers[1] )
            self.assertAlmostEqual( self.chunk_el03[5],
                                    block.stopping_powers[2] )
            self.assertIsNotNone( block.corrections )
            self.assertAlmostEqual( self.chunk_el03[6],
                                    block.corrections[0] )
            self.assertAlmostEqual( self.chunk_el03[7],
                                    block.corrections[1] )
            self.assertAlmostEqual( self.chunk_el03[8],
                                    block.corrections[2] )
            
            # verify the xss array
            self.assertEqual( 9, len( block.xss_array ) )
            for index in range( block.length ):
                
                self.assertAlmostEqual( self.chunk_el03[index],
                                        block.xss_array[index] )
            
        # the data is given explicitly
        block = RadiationStoppingPowerBlock( self.chunk_el03[0:3],
                                             self.chunk_el03[3:6],
                                             self.chunk_el03[6:9] )
        
        verify_block( self, block )

if __name__ == '__main__' :
    
    unittest.main()
