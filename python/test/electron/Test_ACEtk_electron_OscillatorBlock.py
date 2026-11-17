# standard imports
import unittest

# third party imports

# local imports
from ACEtk.electron import OscillatorBlock

class Test_ACEtk_electron_OscillatorBlock( unittest.TestCase ) :
    """Unit test for the OscillatorBlock class."""

    chunk = [ 2.0, 2.0, -2.0, 288.0, 16.59, 11.26 ]

    def test_component( self ) :

        def verify_block( self, block ) :

            # verify content
            self.assertEqual( False, block.empty )
            self.assertEqual( 6, block.length )
            self.assertEqual( "OSC", block.name )

            self.assertEqual( 3, block.NOSC )
            self.assertEqual( 3, block.number_oscillators )
            
            self.assertEqual( 3, len( block.occupation_numbers ) )
            self.assertEqual( 3, len( block.binding_energies ) )
            
            self.assertAlmostEqual( self.chunk[0], block.occupation_numbers[0] )
            self.assertAlmostEqual( self.chunk[1], block.occupation_numbers[1] )
            self.assertAlmostEqual( self.chunk[2], block.occupation_numbers[2] )
            self.assertAlmostEqual( self.chunk[3], block.binding_energies[0] )
            self.assertAlmostEqual( self.chunk[4], block.binding_energies[1] )
            self.assertAlmostEqual( self.chunk[5], block.binding_energies[2] )

            # verify the xss array
            self.assertEqual( 6, len( block.xss_array ) )
            for index in range( block.length ) :

                self.assertAlmostEqual( self.chunk[index],
                                        block.xss_array[index] )

        # the data is given explicitly
        chunk = OscillatorBlock( self.chunk[0:3],
                                                     self.chunk[3:6] )

        verify_block( self, chunk )

if __name__ == '__main__' :

    unittest.main()
