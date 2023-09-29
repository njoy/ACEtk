# standard imports
import unittest

# third party imports

# local imports
from ACEtk.continuous import DelayedNeutronPrecursorData

class Test_ACEtk_DelayedNeutronPrecursorData( unittest.TestCase ) :
    """Unit test for the DelayedNeutronPrecursorData class."""

    chunk = [  2.30000000000E-04,                   0,                   3,
               1.00000000000E-11,   1.00000000000E+00,   2.00000000000E+01,   1.20000000000E-03,
               2.50000000000E-02,   1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 9, chunk.length )
            self.assertEqual( "DelayedNeutronPrecursorData", chunk.name )

            self.assertEqual( 1, chunk.number )

            self.assertAlmostEqual( 2.3e-4, chunk.DEC )
            self.assertAlmostEqual( 2.3e-4, chunk.decay_constant )

            self.assertEqual( 0, chunk.interpolation_data.NB )
            self.assertEqual( 0, chunk.interpolation_data.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.interpolation_data.INT ) )
            self.assertEqual( 0, len( chunk.interpolation_data.interpolants ) )
            self.assertEqual( 0, len( chunk.interpolation_data.NBT ) )
            self.assertEqual( 0, len( chunk.interpolation_data.boundaries ) )

            self.assertEqual( 0, chunk.NB )
            self.assertEqual( 0, chunk.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.INT ) )
            self.assertEqual( 0, len( chunk.interpolants ) )
            self.assertEqual( 0, len( chunk.NBT ) )
            self.assertEqual( 0, len( chunk.boundaries ) )

            self.assertEqual( 3, chunk.NE )
            self.assertEqual( 3, chunk.number_values )

            self.assertEqual( 3, len( chunk.energies ) )
            self.assertAlmostEqual( 1e-11, chunk.energies[0] )
            self.assertAlmostEqual( 1., chunk.energies[1] )
            self.assertAlmostEqual( 20., chunk.energies[2] )

            self.assertEqual( 3, len( chunk.probabilities ) )
            self.assertAlmostEqual( 1.2e-3, chunk.probabilities[0] )
            self.assertAlmostEqual( 2.5e-2, chunk.probabilities[1] )
            self.assertAlmostEqual( 1., chunk.probabilities[2] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = DelayedNeutronPrecursorData(
                  number = 1,
                  constant = 2.3e-4,
                  energies = [ 1e-11, 1., 20. ],
                  probabilities = [ 1.2e-3, 2.5e-2, 1. ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
