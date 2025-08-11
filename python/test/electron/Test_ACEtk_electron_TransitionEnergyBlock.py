# standard imports
import unittest

# third party imports

# local imports
from ACEtk.electron import TransitionEnergyBlock

class Test_ACEtk_electron_TransitionEnergyBlock( unittest.TestCase ) :
    """Unit tests for the TransitionEnergyBlock class."""
    
    chunk_el = [ 7.112, 6.47, 0.9877, 0.9525 ]
    chunk_el03 = [ 7.112001, 6.47 ]
    
    def test_component_el( self ) :
        """Unit test for TransitionEnergyBlock in the el format."""
        
        def verify_block( self, block ) :
            
            # verify content
            self.assertEqual( False, block.empty )
            self.assertEqual( 4, block.length )
            self.assertEqual( "EKT", block.name )
            
            self.assertAlmostEqual( self.chunk_el[0],
                                    block.EDG )
            self.assertAlmostEqual( self.chunk_el[0],
                                    block.k_edge_energy )
            self.assertAlmostEqual( self.chunk_el[1],
                                    block.EEK )
            self.assertAlmostEqual( self.chunk_el[1],
                                    block.k_xray_emission_energy )
            self.assertAlmostEqual( self.chunk_el[2],
                                    block.upper_bremsstrahlung_transition_energy )
            self.assertAlmostEqual( self.chunk_el[3],
                                    block.lower_bremsstrahlung_transition_energy )
            
            # verify the xss array
            self.assertEqual( 4, len( block.xss_array ) )
            for index in range( block.length ) :
                
                self.assertAlmostEqual( self.chunk_el[index],
                                        block.xss_array[index] )
        
        # the data is given explicitly
        block = TransitionEnergyBlock( values = self.chunk_el )
        
        verify_block( self, block )
    
    def test_component_el03( self ) :
        """Unit test for TransitionEnergyBlock in the el format."""
        
        def verify_block( self, block ) :
            
            # verify content
            self.assertEqual( False, block.empty )
            self.assertEqual( 2, block.length )
            self.assertEqual( "EKT", block.name )
            
            self.assertAlmostEqual( self.chunk_el03[0],
                                    block.EDG )
            self.assertAlmostEqual( self.chunk_el03[0],
                                    block.k_edge_energy )
            self.assertAlmostEqual( self.chunk_el03[1],
                                    block.EEK )
            self.assertAlmostEqual( self.chunk_el03[1],
                                    block.k_xray_emission_energy )
            self.assertIsNone( block.upper_bremsstrahlung_transition_energy )
            self.assertIsNone( block.lower_bremsstrahlung_transition_energy )
            
            # verify the xss array
            self.assertEqual( 2, len( block.xss_array ) )
            for index in range( block.length ) :
                
                self.assertAlmostEqual( self.chunk_el03[index],
                                        block.xss_array[index] )
        
        # the data is given explicitly
        block = TransitionEnergyBlock( values = self.chunk_el03 )
        
        verify_block( self, block )

if __name__ == '__main__' :

    unittest.main()
