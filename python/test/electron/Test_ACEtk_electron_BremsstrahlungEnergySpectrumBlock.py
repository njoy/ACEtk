# standard imports
import unittest

# third party imports

# local imports
from ACEtk.electron import BremsstrahlungEnergySpectrumBlock

class Test_ACEtk_electron_BremsstrahlungEnergySpectrumBlock( unittest.TestCase ) :
    """Unit test for the BremsstrahlungEnergySpectrumBlock class."""

    chunk = [ 0.001, 0.25, 0.50, 0.80, 0.9999 ]

    def test_component( self ) :

        def verify_block( self, block ) :

            # verify content
            self.assertEqual( False, block.empty )
            self.assertEqual( 5, block.length )
            self.assertEqual( "RKT", block.name )

            self.assertEqual( 5, block.NRKT )
            self.assertEqual( 5, block.number_photon_energy_ratios )
            self.assertEqual( 5, len( block.photon_energy_ratios ) )
            
            self.assertAlmostEqual( self.chunk[0], block.photon_energy_ratios[0] )
            self.assertAlmostEqual( self.chunk[1], block.photon_energy_ratios[1] )
            self.assertAlmostEqual( self.chunk[2], block.photon_energy_ratios[2] )
            self.assertAlmostEqual( self.chunk[3], block.photon_energy_ratios[3] )
            self.assertAlmostEqual( self.chunk[4], block.photon_energy_ratios[4] )

            # verify the xss array
            self.assertEqual( 5, len( block.xss_array ) )
            for index in range( block.length ) :

                self.assertAlmostEqual( self.chunk[index],
                                        block.xss_array[index] )

        # the data is given explicitly
        chunk = BremsstrahlungEnergySpectrumBlock( self.chunk[0:5] )

        verify_block( self, chunk )

if __name__ == '__main__' :

    unittest.main()
