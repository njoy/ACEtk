# standard imports
import unittest

# third party imports

# local imports
from ACEtk import PhotoatomicElectronBremsstrahlungBlock

class Test_ACEtk_PhotoatomicElectronBremsstrahlungBlock( unittest.TestCase ) :
    """Unit test for the PhotoatomicElectronBremsstrahlungBlock class."""

    chunk = [  10.,  20., 200.,
                1.,   2.,   3. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 6, chunk.length )
            self.assertEqual( "BREML", chunk.name )

            self.assertEqual( 6, len( chunk.xss_array ) )

            self.assertEqual( 3, chunk.NBL )
            self.assertEqual( 3, chunk.number_energy_points )

            self.assertEqual( 3, len( chunk.energies ) )
            self.assertEqual( 3, len( chunk.energy_after_bremsstrahlung ) )

            self.assertAlmostEqual(  10., chunk.energies[0] )
            self.assertAlmostEqual(  20., chunk.energies[1] )
            self.assertAlmostEqual( 200., chunk.energies[2] )
            self.assertAlmostEqual(   1., chunk.energy_after_bremsstrahlung[0] )
            self.assertAlmostEqual(   2., chunk.energy_after_bremsstrahlung[1] )
            self.assertAlmostEqual(   3., chunk.energy_after_bremsstrahlung[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = PhotoatomicElectronBremsstrahlungBlock(
                  energies  = [ 10., 20., 200. ],
                  remaining = [ 1., 2., 3. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
