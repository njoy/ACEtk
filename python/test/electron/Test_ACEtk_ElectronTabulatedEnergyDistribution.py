# standard imports
import unittest

# third party imports

# local imports
from ACEtk import ElectronTabulatedEnergyDistribution

class Test_ACEtk_ElectronTabulatedEnergyDistribution( unittest.TestCase ) :
    """Unit test for the ElectronTabulatedEnergyDistribution class."""

    chunk = [  1.00000000000E+01,  1.00000000000E+02,  9.99000000000E+02,
               0.00000000000E+00,  0.75000000000E+00,  1.00000000000E+00 ]

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 6, chunk.length )
            self.assertEqual( "ElectronTabulatedEnergyDistribution", chunk.name )

            self.assertEqual( 1000., chunk.energy )
            self.assertEqual( 3, chunk.number_outgoing_energies )

            self.assertEqual( 3, len( chunk.outgoing_energies ) )
            self.assertAlmostEqual(  10., chunk.outgoing_energies[0] )
            self.assertAlmostEqual( 999., chunk.outgoing_energies[-1] )

            self.assertEqual( 3, len( chunk.cdf ) )
            self.assertAlmostEqual( 0., chunk.cdf[0] )
            self.assertAlmostEqual( 1., chunk.cdf[-1] )

            # verify the xss array
            xss = chunk.xss_array
            for index in range( chunk.length ) :

                self.assertAlmostEqual( self.chunk[index], xss[index] )

        # the data is given explicitly
        chunk = ElectronTabulatedEnergyDistribution(
                    energy = 1000.,
                    outgoing = [ 10., 100., 999. ],
                    cdf = [ 0.0, 0.75, 1.0 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
