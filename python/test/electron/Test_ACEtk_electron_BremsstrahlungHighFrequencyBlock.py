# standard imports
import unittest

# third party imports

# local imports
from ACEtk.electron import BremsstrahlungHighFrequencyBlock

class Test_ACEtk_electron_BremsstrahlungHighFrequencyBlock( unittest.TestCase ) :
    """Unit test for the BremsstrahlungHighFrequencyBlock class."""

    chunk = [ 0.1, 1.0, 10.0, 0.2, 1.2, 3.0 ]

    def test_component( self ) :

        def verify_block( self, block ) :

            # verify content
            self.assertEqual( False, block.empty )
            self.assertEqual( 6, block.length )
            self.assertEqual( "HFB", block.name )

            self.assertEqual( 3, block.NHFB )
            self.assertEqual( 3, block.number_energy_points )
            
            self.assertEqual( 3, len( block.energies ) )
            self.assertEqual( 3, len( block.cross_sections ) )
            
            self.assertAlmostEqual( self.chunk[0], block.energies[0] )
            self.assertAlmostEqual( self.chunk[1], block.energies[1] )
            self.assertAlmostEqual( self.chunk[2], block.energies[2] )
            self.assertAlmostEqual( self.chunk[3], block.cross_sections[0] )
            self.assertAlmostEqual( self.chunk[4], block.cross_sections[1] )
            self.assertAlmostEqual( self.chunk[5], block.cross_sections[2] )

            # verify the xss array
            self.assertEqual( 6, len( block.xss_array ) )
            for index in range( block.length ) :

                self.assertAlmostEqual( self.chunk[index],
                                        block.xss_array[index] )

        # the data is given explicitly
        chunk = BremsstrahlungHighFrequencyBlock( self.chunk[0:3],
                                                     self.chunk[3:6] )

        verify_block( self, chunk )

if __name__ == '__main__' :

    unittest.main()
