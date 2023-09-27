# standard imports
import unittest

# third party imports

# local imports
from ACEtk.electron import ExcitationBlock

class Test_ACEtk_electron_ExcitationBlock( unittest.TestCase ) :
    """Unit test for the ExcitationBlock class."""

    chunk = [  10.,  20., 200.,
                1.,   2.,   3. ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 6, chunk.length )
            self.assertEqual( "EXCIT", chunk.name )

            self.assertEqual( 6, len( chunk.xss_array ) )

            self.assertEqual( 3, chunk.NXL )
            self.assertEqual( 3, chunk.number_energy_points )

            self.assertEqual( 3, len( chunk.energies ) )
            self.assertEqual( 3, len( chunk.excitation_energy_loss ) )

            self.assertAlmostEqual(  10., chunk.energies[0] )
            self.assertAlmostEqual(  20., chunk.energies[1] )
            self.assertAlmostEqual( 200., chunk.energies[2] )
            self.assertAlmostEqual(   1., chunk.excitation_energy_loss[0] )
            self.assertAlmostEqual(   2., chunk.excitation_energy_loss[1] )
            self.assertAlmostEqual(   3., chunk.excitation_energy_loss[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = ExcitationBlock(
                  energies = [ 10., 20., 200. ],
                  loss     = [ 1., 2., 3. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
